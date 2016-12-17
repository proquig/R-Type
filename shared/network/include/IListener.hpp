#ifndef R_TYPE_ILISTENER_HPP_
#define R_TYPE_ILISTENER_HPP_

#include "IObservable.hpp"
#undef ERROR

class ISocket;
class ISocketPoll;

class IListener : public virtual IObservable
{
public:
  enum State
  {
    NONE = 0,
    ACCEPT = 1,
    ERROR = 2,
  };
public:
  virtual ~IListener() = default;
public:
  virtual ISocket *accept(IObserver *) = 0;
  virtual void close() = 0;
  virtual ISocketPoll *getSocketPoll() = 0;
  virtual bool isClosed() const = 0;
  virtual bool listen(unsigned short = 9696) = 0;
};

#endif //R_TYPE_ILISTENER_HPP_