#include <iostream>
#include <thread>
#include "Server.hpp"
#include "IListener.hpp"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocket.hpp"
#include "IThreadPool.hh"

Server::Server(ISocketFactory *factory, IThreadPool *pool)
    : _cond(nullptr), _socketFactory(factory), _init(false), _listener(nullptr),
    _mutex(nullptr), _pool(pool), _stop(false), _udpSocket(nullptr),
    _waiting(false)
{
  if (_pool)
  {
    _cond = _pool->createCondVar();
    _mutex = _pool->createMutex();
    if (_cond && _mutex)
    {
      _listener = _socketFactory->createListener();
      _udpSocket = _socketFactory->createSocketUDP(this, 4242);
      if (_listener && _udpSocket)
      {
        _listener->addObserver(this);
        _init = true;
      }
    }
  }
}

Server::~Server()
{
  if (_pool)
  {
    _pool->stop();
    if (_cond)
      _pool->deleteCondVar(_cond);
    if (_mutex)
      _pool->deleteMutex(_mutex);
    if (_listener)
      _listener->removeObserver(this);
  }
}

bool Server::init() const
{
  return _init;
}

int Server::run()
{
  std::cout << "Go listen" << std::endl;
  if (!_listener->listen(4296))
    return 0;
  std::cout << "Listen 4296 ok" << std::endl;
  _pool->addTask(_pool->createTask(std::bind(&Server::stop, this, 10)));
  _mutex->lock();
  while (!_stop)
  {
    _waiting = true;
    _cond->wait(_mutex);
    _waiting = false;
  }
  _mutex->unlock();
  return 0;
}

void Server::update(IObservable *o, int status)
{
  static const std::string hello("hello\nhellooo\n");
  struct sockaddr *so = nullptr;

  if (o == _listener)
  {
    if (status == IListener::ERROR)
    {
      _stop = true;
      _cond->signal();
    }
    if (status == IListener::ACCEPT)
    {
      std::cout << "Accept" << std::endl;
      ISocket *socket = nullptr;
      if ((socket = _listener->accept(this)) != nullptr)
      {
        std::cout << "Accept success" << std::endl;
        std::vector<unsigned char> vec(hello.begin(), hello.end());
        socket->write(vec, nullptr);
        _sockets.push_back(socket);
      }
    }
  }
  else if (o == _udpSocket)
  {
    if (status == ISocket::CLOSE)
    {
      std::cout << "Socket UDP closed" << std::endl;
      _udpSocket = nullptr;
    }
    if (status == ISocket::READ)
    {
      std::vector<unsigned char> &ref = _udpSocket->read(&so);
      std::string string(ref.begin(), ref.end());
      _udpSocket->write(std::vector<unsigned char>(hello.begin(), hello.end()), so);
      std::cout << "Received message : \n" << string << std::endl;
      ref.erase(ref.begin(), ref.end());
    }
  }
  else
  {
    std::cout << "Socket event" << std::endl;
  }
}

void Server::stop(unsigned int delay)
{
  if (_cond && _mutex)
  {
    _mutex->lock();
    _cond->wait(_mutex, 1000 * delay);
    _mutex->unlock();
    if (!_stop)
    {
      std::cout << "Stopping server after " << delay << " seconds" << std::endl;
      _stop = true;
      if (_waiting)
        _cond->signal();
    }
  }
}
