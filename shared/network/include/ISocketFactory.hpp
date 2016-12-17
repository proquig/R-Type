#ifndef R_TYPE_ISOCKETFACTORY_HPP_
#define R_TYPE_ISOCKETFACTORY_HPP_

#include <string>

class IListener;
class IObserver;
class ISocket;

class ISocketFactory
{
public:
  virtual ~ISocketFactory() = default;
public:
  virtual IListener* createListener() = 0;
  virtual ISocket* createSocketUDP(IObserver *, unsigned short = 4242) = 0;
  virtual bool hintSockaddr(const std::string &, struct sockaddr &, unsigned short = 4242) = 0;
  virtual void stopPoller() = 0;
};

#endif //R_TYPE_ISOCKETFACTORY_HPP_