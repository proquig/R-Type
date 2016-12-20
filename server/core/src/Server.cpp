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
    _timer(nullptr), _waiting(false)
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
  File *file = new File("./map.txt");

  GameController* gc = _controllerFactory.create(file);
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
  }
  _mutex->unlock();
  return true;
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
    return;
  }
  if (_test)
  {
    //Gestion protocole 1 game
    if (status == ISocket::READ)
    {
      struct sockaddr *addr;
      std::vector<unsigned char> &ref = _test->read(&addr);
      if (ref.size() != 0)
      {
        APacket *packet;
        std::string data(ref.begin(), ref.end());
        //std::cout << "SIZE = " << data.size() << std::endl;
        if ((packet = APacket::create(data)) != nullptr)
          if (packet->getType() == APacket::INPUT_DATA)
            this->handleSocket(addr, packet);
            //for (int i = 0; i < ((InputPacket *) packet)->getInputs().size(); ++i)
            //  std::cout << "INPUT[" << i << "]=" << (int) ((InputPacket *) packet)->getInputs()[i] << std::endl;
        ref.erase(ref.begin(), ref.end());
		delete packet;
      }
    }
    if (status == ISocket::CLOSE)
    {
    }
  }
}

/*
void Server::handleSocket(struct sockaddr *addr, APacket* packet)
{
  InputPacket*		pak;
  int8_t t[][2] = {
		  {0, -1},
		  {0, 1},
		  {-1, 0},
		  {1, 0}
  };

  Player  *player = nullptr;
  int16_t i = -1;
  while (++i < this->_rooms.size()
		 && !this->_rooms[i]->socketIsPresent(addr)
		 && this->_rooms[i]->isFull());
  if (i == this->_rooms.size() ||
	  (!this->_rooms[i]->socketIsPresent(addr)
	   && this->_rooms[i]->isFull()))
  {
	std::cout << "NEW ROOM" << std::endl;
    player = new Player;
	this->_rooms.push_back(new Room(player, addr));
    this->_rooms.back()->sendNotification(_test);
  }
  else if (!this->_rooms[i]->socketIsPresent(addr))
  {
	std::cout << "NEW PLAYER" << std::endl;
    player = new Player;
    this->_rooms[i]->addPlayer(player, addr);
    this->_rooms.back()->sendNotification(_test);
  }
  else
  {
	std::cout << "ROOM NO " << i << "WITH " << this->_rooms[i]->getPlayers().size() << std::endl;
	std::cout << " --- START DEBUG --- " << std::endl;
	for (std::map<struct sockaddr*, Player*>::iterator it = this->_rooms[i]->getPlayers().begin(); it != this->_rooms[i]->getPlayers().end(); ++it)
	{
	  std::cout << "  --- START PLAYER ---  " << std::endl;
	  std::cout << "PTR = " << &it << std::endl;
	  std::cout << "PTR SOCK = " << it->first << std::endl;
	  std::cout << "PTR PLAYER = " << it->second << std::endl;
	  std::cout << "PLAYER ID = " << it->second->getId() << std::endl;
	  std::cout << "  --- START PLAYER ---  " << std::endl;
	}
	std::cout << " --- END DEBUG --- " << std::endl;
	player = this->_rooms[i]->getPlayerFromSock(addr);
	pak = (InputPacket*)packet;
	if (pak->getInputs().size())
	{
	  std::cout << "YEP" << std::endl;
	  player->setX(player->getX() + (t[pak->getInputs()[0] - 3][0] * player->getSpeed()));
	  player->setY(player->getY() + (t[pak->getInputs()[0] - 3][1] * player->getSpeed()));
	  this->_rooms.back()->sendNotification(_test);
	}
  }
}
*/

void Server::handleSocket(struct sockaddr *addr, APacket* packet)
{
  InputPacket*		pak;
  int8_t t[][2] = {
		  {0, -1},
		  {0, 1},
		  {-1, 0},
		  {1, 0}
  };
  Player  *player = nullptr;
  int16_t i = -1;
  while (++i < this->_rooms.size() && !this->_rooms[i]->socketIsPresent(addr));
	if (i == this->_rooms.size())
	{
	  if (!i || this->_rooms.back()->isFull())
	  {
		//std::cout << "NEW ROOM" << std::endl;
		this->_rooms.push_back(new Room(new Player(addr)));
		this->_rooms.back()->sendNotification(_test);
	  }
	  else
	  {
		//std::cout << "NEW PLAYER" << std::endl;
		this->_rooms.back()->addPlayer(new Player(addr));
		this->_rooms.back()->sendNotification(_test);
	  }
	}
	else
	{
	  //std::cout << "PLAYER" << std::endl;
	  if ((player = this->_rooms[i]->getPlayerFromSock(addr)))
	  {
		pak = (InputPacket*)packet;
		if (pak && pak->getInputs().size())
		{
		  player->setX(player->getX() + (t[pak->getInputs()[0] - 3][0] * player->getSpeed()));
		  player->setY(player->getY() + (t[pak->getInputs()[0] - 3][1] * player->getSpeed()));
		  this->_rooms[i]->sendNotification(_test);

		  for (uint8_t j = 0; j < this->_rooms[i]->getPlayers().size(); ++j)
			if (player != this->_rooms[i]->getPlayers()[j])
			{
			  //std::cout << "Player X = " << player->getX() << " & Y = " << player->getY() << std::endl;
			  //std::cout << "Player2 X = " << this->_rooms[i]->getPlayers()[j]->getX() << " & Y = " << this->_rooms[i]->getPlayers()[j]->getY() << std::endl;
			  //std::cout << this->_rooms[i]->getPlayers()[j]->getX() - player->getX() << std::endl;
			  //std::cout << this->_rooms[i]->getPlayers()[j]->getY() - player->getY() << std::endl;
			  if (((this->_rooms[i]->getPlayers()[j]->getX() - player->getX() <= 30) && (this->_rooms[i]->getPlayers()[j]->getX() - player->getX() >= -30))
				  && ((this->_rooms[i]->getPlayers()[j]->getY() - player->getY() <= 15) && (this->_rooms[i]->getPlayers()[j]->getY() - player->getY() >= -15)))
				std::cout << "COLLISION" << std::endl;
			}
		}
	  }
	  else
		  std::cout << "ERROR" << std::endl;
	}
}