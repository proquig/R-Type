#ifndef R_TYPE_SOCKETTCP_HPP_
#define R_TYPE_SOCKETTCP_HPP_

#include "ASocket.hpp"
#include "SocketPoll.hpp"

class SocketTCP : public ASocket
{
protected:
  SocketPoll _socketPoll;
public:
  SocketTCP() = delete;
  SocketTCP(SocketPoller *);
  virtual ~SocketTCP();
public:
  virtual void close();
  virtual ISocketPoll *getSocketPoll();
  virtual void update(IObservable *, int);
  virtual void write(const std::vector<unsigned char> &, struct sockaddr *);
protected:
  virtual bool _read();
  virtual bool _write();
};

#endif //R_TYPE_SOCKETTCP_HPP_