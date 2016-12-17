#include "SocketPoll.hpp"

SocketPoll::SocketPoll(SocketPoller *poller)
    : ASocketPoll(), _fd(-1), _poller(poller)
{
}

SocketPoll::~SocketPoll()
{
}

void SocketPoll::setFd(int fd)
{
  if (_fd < 0 && fd >= 0)
  {
    _fd = fd;
    waitState(ISocketPoll::READ);
    _poller->add(this);
  }
}

int SocketPoll::getFd() const
{
  return _fd;
}

void SocketPoll::waitState(ISocketPoll::State state)
{
  ASocketPoll::waitState(state);
}

void SocketPoll::unwaitState(ISocketPoll::State state)
{
  ASocketPoll::unwaitState(state);
}
