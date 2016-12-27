#include <iostream>
#include <thread>
#include "Server.hpp"
#include "Room.hpp"
#include "APacket.hh"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocket.hpp"
#include "ISocketFactory.hpp"
#include "IThreadPool.hh"
#include "ITimer.hpp"
#include "File.hh"
#include "InputPacket.hh"
#include "GameDataPacket.hh"

Server::Server(unsigned short port)
    : _socketFactory(nullptr), _pool(nullptr), _stop(false),
    _test(nullptr), _waiting(false)
{
  _dlManager.add(0, "threadpool", "");
  _dlManager.add(0, "rtype_network", "");
  _dlManager.add(0, "monster", "");
}

Server::~Server()
{
  _network.removeObserver(this);
  if (_socketFactory)
  {
    _network.stop();
    reinterpret_cast<void *(*)(ISocketFactory *)>(_dic[1]->at("destroy"))(_socketFactory);
  }
  if (_pool)
  {
    _pool->stop();
    reinterpret_cast<void *(*)(IThreadPool *)>(_dic[0]->at("destroy"))(_pool);
  }
  if (_monster)
	reinterpret_cast<void *(*)(Monster *)>(_dic[2]->at("destroy"))(_monster);
  for (Dictionary dic : _dic)
  {
    if (dic)
      delete dic;
  }
}


bool Server::game_test(unsigned short port, unsigned short time)
{
  //File *file = new File("./map.txt");

  //GameController* gc = _controllerFactory.create(file);
  if (port != 0)
    _test = _socketFactory->createSocketUDP(this, port);
  if (time != 0)
    _pool->addTask(_pool->createTask(std::bind(&Server::stop, this, time)));
  return true;
}

bool Server::init()
{
  Dictionary dic;
  std::string error;

  if (!_dlManager.handler.loadAll(error))
  {
    std::cout << "Failed loading library module : " << error << std::endl;
    return false;
  }
  std::cout << "Library load success" << std::endl;
  if ((dic = _dlManager.handler.getDictionaryByName("threadpool")) != NULL
      && !(*_dic.insert(_dic.end(), dic))->empty()
      && (_pool = reinterpret_cast<IThreadPool *(*)(size_t)>(_dic.back()->at("instantiate"))(4)) != nullptr
      && ((_cond = _pool->createCondVar()) != nullptr)
      && ((_mutex = _pool->createMutex()) != nullptr))
    std::cout << "pool spawned" << std::endl;
  else
    return false;
  if ((dic = _dlManager.handler.getDictionaryByName("rtype_network")) != NULL
      && !(*_dic.insert(_dic.end(), dic))->empty()
      && (_socketFactory = reinterpret_cast<ISocketFactory *(*)(IThreadPool*)>(_dic.back()->at("instantiate"))(_pool)) != nullptr)
    std::cout << "_socketFactory spawned" << std::endl;
  else
    return false;
  _network = NetworkHandler(_socketFactory);
  _network.addObserver(this);
  return (_network.getState() == NetworkHandler::RUNNING);
}

bool Server::run()
{
  _mutex->lock();
  while (!_stop)
  {
    _waiting = true;
    _cond->wait(_mutex, 100);
    _waiting = false;
    if (!_stop)
	  this->loop();
  }
  _mutex->unlock();
  return true;
}

void Server::loop()
{
  std::vector<std::pair<std::string, struct sockaddr*>> *vector;
  APacket *packet;

  for (Room* room :  this->_rooms)
	this->handleRoom(room);
  for (Room* room : this->_rooms)
    for (Player* player : room->getPlayers())
      {
        //this->handleCollision(room, player);
        this->realizeMovement(room, player);
      }

  //PACKET EMISSION
  if (_test && _rooms.size())
	_rooms.front()->sendNotification(_test);
  //PACKET RECEPTION
  if ((vector = _packets.popAll()) != nullptr && vector->size() != 0)
    for (std::pair<std::string, struct sockaddr*> pair : (*vector))
      if ((packet = APacket::create(pair.first)) != nullptr)
        if (packet->getType() == APacket::INPUT_DATA)
          this->handleSocket(pair.second, packet);
}

void Server::stop(unsigned int delay)
{
  std::this_thread::sleep_for(std::chrono::seconds(delay));
  if (!_stop)
  {
    std::cout << "Stopping server after " << delay << " seconds" << std::endl;
    _stop = true;
    if (_waiting)
      _cond->signal();
  }
}

void Server::update(IObservable *o, int status)
{
  if (o == &_network)
  {
    if (status == NetworkHandler::LISTENER_ERROR)
      stop(0);
  }
  if (_test && o == _test)
  {
    //Gestion protocole 1 game
    if (status == ISocket::READ)
    {
      struct sockaddr *addr;
      std::vector<unsigned char> &ref = _test->read(&addr);
      if (ref.size() != 0)
      {
        _packets.push(std::make_pair(std::string(ref.begin(), ref.end()), addr));
        ref.erase(ref.begin(), ref.end());
      }
    }
    if (status == ISocket::CLOSE)
    {
    }
  }
}

void Server::handleSocket(struct sockaddr *addr, APacket* packet)
{
  Player  *player = nullptr;
  int16_t i = -1;
  while (++i < this->_rooms.size() && !this->_rooms[i]->socketIsPresent(addr));
	if (i == this->_rooms.size())
	{
	  if (!i || this->_rooms.back()->isFull())
		this->createRoom(addr);
	  else
		this->addPlayer(addr);
	}
	else
	{
	  if ((player = this->_rooms[i]->getPlayerFromSock(addr)))
            this->handleMovement(this->_rooms[i], player, (InputPacket*)packet);
	  else
            std::cout << "ERROR" << std::endl;
	}
}

void Server::createRoom(struct sockaddr *sock)
{
  Room*		room = new Room;
  Player*	player = new Player(sock);

  room->addPlayer(player);
  room->getGameController()->getGame()->addPlayer(player);
  this->_rooms.push_back(room);
  this->_rooms.back()->sendNotification(_test);
}

void Server::addPlayer(struct sockaddr *sock)
{
  Player*	player = new Player(sock);

  this->_rooms.back()->addPlayer(player);
  this->_rooms.back()->getGameController()->getGame()->addPlayer(player);
  this->_rooms.back()->sendNotification(_test);
}

void Server::handleRoom(Room* room)
{
 // std::cout << room->getGameController()->getGame()->getMap().size() << std::endl;
  this->handleCollision(room);
  for (RType::IElement* elem : room->getGameController()->getGame()->getMap())
	if (elem->getType() == RType::BULLET)
	  if (elem->getX() > 799)
	  {
		room->getGameController()->getGame()->deleteElem(elem);
		//delete elem;
		std::cout << "ELEM DELETED" << std::endl;
	  }
	  else
		elem->setX(elem->getX() + uint16_t(10));
  this->handleMonsters(room);
}

void Server::handleMonsters(Room* room)
{
  uint16_t rand;
  Dictionary dic;
  std::srand(std::time(0));
  rand = (uint16_t)(std::rand() % 10);
  if (rand == 1)
  {
	std::cout << "BITCH" << std::endl;
	if ((dic = _dlManager.handler.getDictionaryByName("monster")) != NULL
		&& !(*_dic.insert(_dic.end(), dic))->empty()
		&& (_monster = reinterpret_cast<Monster *(*)(int, int, int, ElementFactory*)>(_dic.back()->at("new"))(42, 450, 200, room->getGameController()->getElementFactory())) != nullptr)
	{
	  this->_monster->setType(RType::MONSTER);
	  room->getGameController()->getGame()->addElem(this->_monster);
	  std::cout << "_monster spawned" << std::endl;
	}
  }
  for (uint8_t i = 0; i < room->getGameController()->getGame()->getMap().size(); ++i)
	if (room->getGameController()->getGame()->getMap()[i]->getType() == RType::MONSTER)
	  if (!((Monster*)room->getGameController()->getGame()->getMap()[i])->move())
		room->getGameController()->getGame()->addElem(((Monster*)room->getGameController()->getGame()->getMap()[i])->shot());
}

void Server::handleMovement(Room* room, Player* player, InputPacket* packet)
{
  if (packet && packet->getInputs().size())
  {
    std::vector<uint16_t> inputs = packet->getInputs();
    std::vector<uint16_t> &ref = _inputs[player];
    ref.resize(0);
    ref.insert(ref.end(), inputs.begin(), inputs.end());
  }
}

void Server::realizeMovement(Room *room, Player *player)
{
  std::vector<uint16_t> &ref = _inputs[player];
  uint16_t input = 0;

  if (ref.size() == 0)
    return;
  input = ref.back();
  ref.pop_back();
  if ((input & RType::LEFT) != (input & RType::RIGHT))
  {
	int16_t dir = (int16_t)((input & RType::LEFT) ? -1 : 1);
	if (((player->getX() + (dir * player->getSpeed())) > 0 && ((player->getX() + (dir * player->getSpeed())) < 800)))
	  player->setX(player->getX() + (dir * player->getSpeed()));
  }
  if ((input & RType::UP) != (input & RType::DOWN))
  {
    int16_t dir = (int16_t)((input & RType::UP) ? -1 : 1);
	if (((player->getY() + (dir * player->getSpeed())) > 0 && ((player->getY() + (dir * player->getSpeed())) < 450)))
	  player->setY(player->getY() + (dir * player->getSpeed()));
  }
  if (input & RType::SPACE)
  {
	std::cout << "BULLET" << std::endl;
    RType::AElement *elem;
    elem = room->getGameController()->getElementFactory()->create(player->getId(), -1, RType::MISSILE,
                                                                 player->getX() + (player->getSizeX() / 2) + 1,
                                                                 player->getY(), 100, 5, 5, 100, 0,
                                                                 player->getSpeed() + 1);
    room->getGameController()->getGame()->addElem(elem);
  }
}

void Server::handleCollision(Room* room)
{
  //std::cout << "HANDLE COLLISION" << std::endl;
  for (Player* pl : room->getPlayers())
	//if (player != pl)
	room->getGameController()->handleCollisions();
}
