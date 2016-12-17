#ifndef R_TYPE_SOCKETPOLL_HPP_
#define R_TYPE_SOCKETPOLL_HPP_

#include "ASocketPoll.hpp"
#include "Observable.hpp"
#include "SocketPoller.hpp"

class SocketPoll : public ASocketPoll, public Observable
{
protected:
  int _fd;
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