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
        IPacket *packet;
        std::string data(ref.begin(), ref.end());
        std::cout << "SIZE = " << data.size() << std::endl;
        if ((packet = APacket::create(data)) != nullptr)
          if (packet->getType() == APacket::INPUT_DATA)
          {
            this->handleSocket(addr);
            for (int i = 0; i < ((InputPacket *) packet)->getInputs().size(); ++i)
              std::cout << "INPUT[" << i << "]=" << (int) ((InputPacket *) packet)->getInputs()[i] << std::endl;
          }
        //_test->write(ref, addr);
        //std::cout << ref.size() << std::endl;
        ref.erase(ref.begin(), ref.end());
      }
    }
    if (status == ISocket::CLOSE)
    {
    }
  }
}

void Server::handleSocket(struct sockaddr *addr)
{
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
    this->_rooms.back()->sendNotification(_test);
}