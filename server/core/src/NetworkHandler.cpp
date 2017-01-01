#include <iostream>
#include "NetworkHandler.hpp"
#include "IListener.hpp"
#include "ISocket.hpp"
#include "ISocketFactory.hpp"

NetworkHandler::NetworkHandler(ISocketFactory *factory, unsigned short port)
    : _factory(factory), _state(PRE_INIT)
{
  if (_factory)
  {
    _state = INIT;
    if ((_listener = _factory->createListener()) != nullptr)
      _listener->addObserver(this);
    if (_listener->listen(port))
      _state = RUNNING;
  }
}

NetworkHandler::~NetworkHandler()
{
}

NetworkHandler::State NetworkHandler::getState() const
{
  return _state;
}

void NetworkHandler::update(IObservable *o, int status)
{
  //Gestion protocole TCP - lobbys etc...
  if (o == _listener)
  {
    if (status == IListener::ERROR)
      notify(LISTENER_ERROR);
    if (status == IListener::ACCEPT)
    {
      ISocket *socket = nullptr;
      if ((socket = _listener->accept(this)) != nullptr)
        _sockets.push_back(socket);
      socket->addObserver(this);
    }
  }
  else
    std::cerr << "TCP socket event" << std::endl;
}

void NetworkHandler::stop()
{
  if (_factory)
    _factory->stopPoller();
}
