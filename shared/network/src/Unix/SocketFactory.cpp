#include <cstring>
#include <netdb.h>
#include "SocketFactory.hpp"
#include "Listener.hpp"
#include "SocketUDP.hpp"

SocketFactory::SocketFactory(IThreadPool *pool) : _poller(pool)
{
}

IListener *SocketFactory::createListener()
{
  if (!_poller.getThreadpool())
    return nullptr;
  return new Listener(&_poller);
}

ISocket *SocketFactory::createSocketUDP(IObserver *obs, unsigned short port)
{
  if (!_poller.getThreadpool())
    return nullptr;
  return new SocketUDP(&_poller, obs, port);
}

bool SocketFactory::hintSockaddr(const std::string &ip, struct sockaddr &addr, unsigned short port)
{
  addrinfo hint = {AF_INET, SOCK_DGRAM, 0, 0, 0, nullptr, nullptr, nullptr};
  addrinfo *info = nullptr;
  if (getaddrinfo(ip.c_str(), nullptr, &hint, &info) == 0)
    {
      addr = *info->ai_addr;
      ((struct sockaddr_in *)&addr)->sin_port = htons(port);
      freeaddrinfo(info);
      return true;
    }
  return false;
}

void SocketFactory::stopPoller()
{
  if (_poller.getThreadpool())
    _poller.stop();
}
