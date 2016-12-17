#include <unistd.h>
#include <netinet/in.h>
#include "SocketTCP.hpp"

#define BUFF_READ 8192

SocketTCP::SocketTCP(SocketPoller *poller)
    : ASocket(), _socketPoll(poller), _addrlen(sizeof(struct sockaddr))
{
  _close = false;
  _socketPoll.addObserver(this);
}

SocketTCP::~SocketTCP()
{
  _socketPoll.removeObserver(this);
}

void SocketTCP::close()
{
  ASocket::close();
  _socketPoll.unregister();
  notify(ISocket::CLOSE);
}

socklen_t* SocketTCP::getAddrlen()
{
  return &_addrlen;
}

ISocketPoll *SocketTCP::getSocketPoll()
{
  return &_socketPoll;
}

void SocketTCP::update(IObservable *o, int status)
{
  if (o == &_socketPoll)
  {
    if (status & ISocketPoll::READ)
    {
      if (_read())
        notify(ISocket::READ);
      else
        close();
    }
    if (status & ISocketPoll::WRITE && !_write())
      close();
  }
}

void SocketTCP::write(const std::vector<unsigned char> &buff, struct sockaddr *so)
{
  ASocket::write(buff, so);
  _socketPoll.waitState(ISocketPoll::WRITE);
}

bool SocketTCP::_read()
{
  unsigned long len;
  ssize_t ret;

  len = _buffIn.size();
  _buffIn.resize(len + BUFF_READ, 0);
  if ((ret = ::read(_socketPoll.getFd(), (&_buffIn.front()) + len, BUFF_READ)) <= 0)
  {
    _buffIn.resize(len);
    return false;
  }
  else
    _buffIn.resize(len + ret);
  return true;
}

bool SocketTCP::_write()
{
  size_t len;
  ssize_t ret;

  if ((len = _buffOut.size()) == 0)
    return false;
  if ((ret = ::write(_socketPoll.getFd(), &_buffOut.front(), len)) <= 0)
      return false;
  else
  {
    _buffOut.erase(_buffOut.begin(), _buffOut.begin() + ret);
    if (_buffOut.size() == 0)
      _socketPoll.unwaitState(ISocketPoll::WRITE);
  }
  return true;
}
