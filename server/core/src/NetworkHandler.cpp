#include "NetworkHandler.hpp"
#include "IListener.hpp"
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

void NetworkHandler::update(IObservable *, int)
{
}

void NetworkHandler::stop()
{
  if (_factory)
    _factory->stopPoller();
}
