#ifndef R_TYPE_ISOCKETPOLL_HPP_
#define R_TYPE_ISOCKETPOLL_HPP_

#include "IObservable.hpp"
#undef ERROR

class ISocketPoll : public virtual IObservable
{
public:
  enum State
  {
    NONE = 0,
    READ = 1,
    WRITE = 2,
    ERROR = 4,
    CLOSE = 8
  };
public:
  virtual ~ISocketPoll() = default;
public:
  virtual int getState() = 0;
  virtual void setFd(int fd) = 0;
  virtual int getFd() const = 0;
  virtual void unregister() = 0;
  virtual void waitState(State) = 0;
  virtual void unwaitState(State) = 0;
};

#endif //R_TYPE_ISOCKETPOLL_HPP_