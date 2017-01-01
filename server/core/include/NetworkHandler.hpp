#ifndef R_TYPE_NETWORKHANDLER_HPP_
#define R_TYPE_NETWORKHANDLER_HPP_

#include <vector>
#include "IObserver.hpp"
#include "Observable.hpp"

class IListener;
class ISocket;
class ISocketFactory;

class NetworkHandler : public Observable, public IObserver
{
public:
  enum State
  {
    PRE_INIT,
    INIT,
    RUNNING,
    LISTENER_ERROR,
  };
protected:
  ISocketFactory *_factory;
  IListener *_listener;
  State _state;
  std::vector<ISocket*> _sockets;
public:
  NetworkHandler(ISocketFactory *socketFactory = nullptr, unsigned short port = 5454);
  virtual ~NetworkHandler();
public:
  virtual State getState() const;
  virtual void update(IObservable*, int);
  virtual void stop();
};

#endif //R_TYPE_NETWORKHANDLER_HPP_