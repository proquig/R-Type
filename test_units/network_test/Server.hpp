#ifndef R_TYPE_SERVER_HPP_
#define R_TYPE_SERVER_HPP_

#include <string>
#include <vector>
#include "IObserver.hpp"
#include "ISocketFactory.hpp"

class ICondVar;
class IListener;
class IMutex;
class ISocket;
class IThreadPool;

class Server : public IObserver
{
protected:
  ICondVar *_cond;
  ISocketFactory *_factory;
  bool _init;
  IListener *_listener;
  IMutex *_mutex;
  IThreadPool *_pool;
  std::vector<ISocket*> _sockets;
  bool _stop;
  ISocket *_udpSocket;
  bool _waiting;
public:
  Server(ISocketFactory *factory, IThreadPool *pool);
  virtual ~Server();
public:
  virtual bool init() const;
  virtual int run();
  virtual void update(IObservable *, int);
protected:
  virtual void stop(unsigned int);
};

#endif //R_TYPE_SERVER_HPP_