#ifndef R_TYPE_ASOCKET_HPP_
#define R_TYPE_ASOCKET_HPP_

#include "ISocket.hpp"
#include "IObserver.hpp"
#include "Observable.hpp"

#ifdef RT_UNIX
  #include <sys/socket.h>
#elif RT_WIN
  #define WIN32_LEAN_AND_MEAN
  #include <Winsock2.h>
#endif

class ASocket : public ISocket, public IObserver, public Observable
{
protected:
  std::vector<unsigned char> _buffIn;
  std::vector<unsigned char> _buffOut;
  bool _close;
  struct sockaddr _so;
public:
  ASocket();
  virtual ~ASocket() = default;
public:
  virtual void close();
  virtual bool isClosed() const;
  virtual struct sockaddr* getSockaddr();
  virtual std::vector<unsigned char>& read(struct sockaddr **);
  virtual void write(const std::vector<unsigned char> &, struct sockaddr *);
};

#endif //R_TYPE_ASOCKET_HPP_