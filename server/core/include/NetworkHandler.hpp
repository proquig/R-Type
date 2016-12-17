#ifndef R_TYPE_NETWORKHANDLER_HPP_
#define R_TYPE_NETWORKHANDLER_HPP_

#include "IObserver.hpp"

class IListener;
class ISocketFactory;

class NetworkHandler : public IObserver
{
public:
  enum State
  {
    PRE_INIT,
    INIT,
    RUNNING,
    STOP,
  };
protected:
  ISocketFactory *_factory;
  IListener *_listener;
  State _state;
public:
  NetworkHandler(ISocketFactory *socketFactory = nullptr, unsigned short port = 5454);
  virtual ~NetworkHandler();
public:
  virtual State getState() const;
  virtual void update(IObservable*, int);
  virtual void stop();
};

#endif //R_TYPE_NETWORKHANDLER_HPP_