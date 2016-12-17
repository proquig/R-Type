#ifndef R_TYPE_LISTENER_HPP_
#define R_TYPE_LISTENER_HPP_

#include "IListener.hpp"
#include "IObserver.hpp"
#include "Observable.hpp"
#include "SocketPoll.hpp"

class Listener : public IListener, public Observable, public IObserver
{
protected:
  bool _close;
  SocketPoller *_poller;
  unsigned short _port;
  SocketPoll _socketPoll;
public:
  Listener(SocketPoller *);
  virtual ~Listener();
public:
  virtual ISocket *accept(IObserver *);
  virtual void close();
  virtual ISocketPoll *getSocketPoll();
  virtual bool isClosed() const;
  virtual bool listen(unsigned short);
  virtual void update(IObservable *, int);
};

#endif //R_TYPE_LISTENER_HPP_