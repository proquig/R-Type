#ifndef R_TYPE_NETWORKHANDLER_HPP_
#define R_TYPE_NETWORKHANDLER_HPP_

#include "IObserver.hpp"

class NetworkHandler : public IObserver
{
public:
  NetworkHandler() = default;
  virtual ~NetworkHandler() = default;
public:
  virtual void update(IObservable*, int);
};

#endif //R_TYPE_NETWORKHANDLER_HPP_