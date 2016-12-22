#include <iostream>
#include <thread>
#include <InputPacket.hh>
#include <GameDataPacket.hh>
#include "Server.hpp"
#include "APacket.hh"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocket.hpp"
#include "ISocketFactory.hpp"
#include "IThreadPool.hh"
#include "ITimer.hpp"
#include "File.hh"

Server::Server(unsigned short port)
    : _socketFactory(nullptr), _pool(nullptr), _stop(false),
    _timer(nullptr), _test(nullptr), _waiting(false), _loop(0)
{
  _dlManager.add(0, "threadpool", "");
  _dlManager.add(0, "rtype_network", "");
  _dlManager.add(0, "rtype_timer", "");
}

Server::~Server()
{
  _network.removeObserver(this);
  if (_timer)
  {
    _timer->stop();
    reinterpret_cast<void *(*)(ITimer *)>(_dic[1]->at("destroy"))(_timer);
  }
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
  if ((dic = _dlManager.handler.getDictionaryByName("rtype_timer")) != NULL
      && !(*_dic.insert(_dic.end(), dic))->empty()
      && (_timer = reinterpret_cast<ITimer *(*)(IThreadPool*)>(_dic.back()->at("instantiate"))(_pool)) != nullptr)
    std::cout << "timer spawned" << std::endl;
  else
    return false;
  _network = NetworkHandler(_socketFactory);
  _network.addObserver(this);
  _timer->setTimer(50);
  _timer->addObserver(this);
  return (_network.getState() == NetworkHandler::RUNNING);
}

bool Server::run()
{
  _mutex->lock();
  while (!_stop)
  {
    _waiting = true;
    _cond->wait(_mutex);
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

  //PACKET EMISSION
  if (_test && _rooms.size())
	_rooms.front()->sendNotification(_test);
  //PACKET RECEPTION
  if ((vector = _packets.popAll()) != nullptr && vector->size() != 0)
	while (vector->size() != 0)
	{
	  std::pair<std::string, struct sockaddr*> pair = vector->back();
	  if ((packet = APacket::create(pair.first)) != nullptr)
		if (packet->getType() == APacket::INPUT_DATA)
		  this->handleSocket(pair.second, packet);
	  vector->pop_back();
	}
  //UPDATE
  if (this->_loop++ == 100)
  {
	for (uint8_t i = 0; i < this->_rooms.size(); ++i)
	  for (uint8_t j = 0; j < this->_rooms[i]->getGameController()->getGame()->getScene()->getMap().size(); ++j)
		if (this->_rooms[i]->getGameController()->getGame()->getScene()->getMap()[j]->getType() == AElement::BULLET)
		  this->_rooms[i]->getGameController()->getGame()->getScene()->getMap()[j]->setX(
				  this->_rooms[i]->getGameController()->getGame()->getScene()->getMap()[j]->getX() +
				  1);//this->_rooms[i]->getGameController()->getGame()->getScene()->getMap()[j]->getSpeed());
	for (uint8_t i = 0; i < this->_rooms.size(); ++i)
	  for (uint8_t j = 0; j < this->_rooms[i]->getPlayers().size(); ++j)
		this->handleCollision(this->_rooms[i], this->_rooms[i]->getPlayers()[j]);
	  this->_loop = 0;
  }
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
  if (o == _timer)
  {
    if (_waiting)
      _cond->signal();
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
        //if (_waiting)
          //_cond->signal();
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
	  {
		this->handleMovement(this->_rooms[i], player, (InputPacket*)packet);
		this->handleCollision(this->_rooms[i], player);
	  }
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

void Server::handleMovement(Room* room, Player* player, InputPacket* packet)
{
  if (packet && packet->getInputs().size())
	for (uint16_t input : packet->getInputs())
	{
	  if (input > 2 && input < 7)
	  {
		player->setX(player->getX() + (mov[input - 3][0] * player->getSpeed()));
		player->setY(player->getY() + (mov[input - 3][1] * player->getSpeed()));
	  }
	  else if (input == 2)
	  {
		AElement *elem;
		elem = room->getGameController()->getElementFactory().create(-1, -1, AElement::BULLET,
															  player->getX() + (player->getSizeX() / 2) + 1,
															  player->getY(), 100, 5, 5, 100, 0,
															  player->getSpeed() + 1);
		room->getGameController()->getGame()->getScene()->addElem(elem);
	  }
	}
}

void Server::handleCollision(Room* room, Player* player)
{
  for (uint8_t i = 0; i < room->getPlayers().size(); ++i)
	if (player != room->getPlayers()[i])
	  room->getGameController()->handleCollisions();
}
