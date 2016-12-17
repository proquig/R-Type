#include <netinet/in.h>
#include <cstring>
#include "Listener.hpp"
#include "SocketTCP.hpp"

Listener::Listener(SocketPoller *poller)
    : _close(true), _poller(poller), _port(0), _socketPoll(poller)
{
  _socketPoll.addObserver(this);
}

Listener::~Listener()
{
  _socketPoll.removeObserver(this);
}

ISocket *Listener::accept(IObserver *obs)
{
  int fd;
  int socketFd;
  ISocket *socket;

  fd = _socketPoll.getFd();
  if (fd < 0 || (socket = new SocketTCP(_poller)) == nullptr)
    return nullptr;
  if ((socketFd = ::accept(fd, socket->getSockaddr(), static_cast<SocketTCP *>(socket)->getAddrlen())) < 0)
  {
    delete socket;
    return nullptr;
  }
  if (obs)
    socket->addObserver(obs);
  socket->getSocketPoll()->setFd(socketFd);
  return socket;
}

void Listener::close()
{
  _close = true;
}

ISocketPoll *Listener::getSocketPoll()
{
  return &_socketPoll;
}

bool Listener::isClosed() const
{
  return _close;
}

bool Listener::listen(unsigned short port)
{
  int fd;
  struct sockaddr_in si;
  int enable = 1;

  if ((fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) != -1)
    if (setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(int)) >= 0)
    {
      memset(&si, 0, sizeof(si));
      si.sin_family = AF_INET;
      si.sin_port = htons(port);
      si.sin_addr.s_addr = htonl(INADDR_ANY);
      if (bind(fd, (struct sockaddr *) &si, sizeof(si)) != -1)
        if (!::listen(fd, SOMAXCONN))
        {
          _port = ntohs(si.sin_port);
          _socketPoll.setFd(fd);
          return true;
        }
    }
  return false;
}

void Listener::update(IObservable *o, int status)
{
  if (o == &_socketPoll)
  {
    if (status & ISocketPoll::ERROR)
    {
      _socketPoll.unregister();
      notify(IListener::ERROR);
    } else if (status & ISocketPoll::READ)
      notify(IListener::ACCEPT);
  }
}
