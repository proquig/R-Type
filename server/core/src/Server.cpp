#include <iostream>
#include <thread>
#include "ICondVar.hh"
#include "IMutex.hh"
#include "IThreadPool.hh"
#include "Server.hpp"

Server::Server(unsigned short port)
    : _dic(std::make_pair(nullptr, nullptr)), _stop(false), _waiting(false)
{
  _dlManager.add(0, "threadpool", "");
  _dlManager.add(0, "rtype_network", "");
}

Server::~Server()
{
  if (_socketFactory)
  {
    _network.stop();
    reinterpret_cast<void *(*)(ISocketFactory *)>(_dic.second->at("destroy"))(_socketFactory);
  }
  if (_pool)
  {
    _pool->stop();
    reinterpret_cast<void *(*)(IThreadPool *)>(_dic.first->at("destroy"))(_pool);
  }
  if (_dic.first)
    delete _dic.first;
  if (_dic.second)
    delete _dic.second;
}


bool Server::game_test(unsigned short port, unsigned short time)
{
  if (port != 0)
  {
  }
  if (time != 0)
    _pool->addTask(_pool->createTask(std::bind(&Server::stop, this, time)));
  return true;
}

bool Server::init()
{
  std::string error;

  if (!_dlManager.handler.loadAll(error))
  {
    std::cout << "Failed loading library module : " << error << std::endl;
    return false;
  }
  std::cout << "Library load success" << std::endl;
  if ((_dic.first = _dlManager.handler.getDictionaryByName("threadpool")) != NULL
      && !_dic.first->empty()
      && (_pool = reinterpret_cast<IThreadPool *(*)(size_t)>(_dic.first->at("instantiate"))(4)) != nullptr
      && ((_cond = _pool->createCondVar()) != nullptr)
      && ((_mutex = _pool->createMutex()) != nullptr))
    std::cout << "pool spawned" << std::endl;
  else
    return false;
  if ((_dic.second = _dlManager.handler.getDictionaryByName("rtype_network")) != NULL
      && !_dic.second->empty()
    && (_socketFactory = reinterpret_cast<ISocketFactory *(*)(IThreadPool*)>(_dic.second->at("instantiate"))(_pool)) != nullptr)
    std::cout << "socketFactory spawned" << std::endl;
  else
    return false;
  _network = NetworkHandler(_socketFactory);
  return true;
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
