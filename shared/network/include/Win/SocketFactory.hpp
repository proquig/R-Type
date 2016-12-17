#ifndef R_TYPE_SOCKETFACTORY_HPP_
#define R_TYPE_SOCKETFACTORY_HPP_

#include "ISocketFactory.hpp"
#include "SocketPoller.hpp"

class SocketFactory : public ISocketFactory
{
protected:
  SocketPoller _poller;
public:
  SocketFactory();
  virtual ~SocketFactory();
public:
  virtual void bindThreadpool(IThreadPool*);
  virtual IListener* createListener();
  virtual ISocket* createSocketUDP(IObserver *, unsigned short);
  virtual bool hintSockaddr(const std::string &, struct sockaddr &, unsigned short = 4242);
  virtual void stopPoller();
};

#endif //R_TYPE_SOCKETFACTORY_HPP_