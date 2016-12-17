#include "SocketPoll.hpp"
#include "SocketPoller.hpp"

SocketPoll::SocketPoll(SocketPoller *poller)
  : ASocketPoll(), _fd(INVALID_SOCKET), _poller(poller)
{
}

SocketPoll::~SocketPoll()
{
}

void SocketPoll::setFd(int fd)
{
  if (_fd == INVALID_SOCKET && fd != INVALID_SOCKET)
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
