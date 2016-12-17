#ifndef R_TYPE_SOCKETUDP_HPP_
#define R_TYPE_SOCKETUDP_HPP_

#include <list>
#include <map>
#include "ASocket.hpp"
#include "SocketPoll.hpp"

class SocketUDP : public ASocket
{
protected:
  std::map<struct sockaddr_storage*, std::list<std::vector<unsigned char>>> _listIn;
  std::list<std::pair<std::vector<unsigned char>, struct sockaddr*>> _listOut;
  unsigned short _port;
  SocketPoll _socketPoll;
public:
  SocketUDP() = delete;
  SocketUDP(SocketPoller *, IObserver *, unsigned short port = 4242);
  virtual ~SocketUDP();
public:
  virtual void close();
  virtual ISocketPoll *getSocketPoll();
  virtual void update(IObservable *, int);
  virtual std::vector<unsigned char>& read(struct sockaddr **);
  virtual void write(const std::vector<unsigned char> &, struct sockaddr *);
protected:
  virtual bool _read();
  virtual bool _write();
};

#endif //R_TYPE_SOCKETUDP_HPP_