#include "Listener.hpp"

Listener::Listener(SocketPoller *poller)
  : _close(true), _poller(poller), _port(0), _socketPoll(poller)
{
  _socketPoll.addObserver(this);
}

Listener::~Listener()
{
  _socketPoll.removeObserver(this);
}

ISocket * Listener::accept(IObserver *)
{
  return nullptr;
}

void Listener::close()
{
}

ISocketPoll * Listener::getSocketPoll()
{
  return nullptr;
}

bool Listener::isClosed() const
{
  return false;
}

bool Listener::listen(unsigned short)
{
  return true;
}

void Listener::update(IObservable *, int)
{
}
