#ifndef R_TYPE_SOCKETPOLL_HPP_
#define R_TYPE_SOCKETPOLL_HPP_

#include <WinSock2.h>
#include "ASocketPoll.hpp"
#include "Observable.hpp"

class SocketPoller;

class SocketPoll : public ASocketPoll, public Observable
{
protected:
  SOCKET _fd;
  SocketPoller *_poller;
public:
  SocketPoll(SocketPoller *);
  virtual ~SocketPoll();
public:
  virtual void setFd(int fd);
  virtual int getFd() const;
  virtual void waitState(State);
  virtual void unwaitState(State);
};

#endif //R_TYPE_SOCKETPOLL_HPP_