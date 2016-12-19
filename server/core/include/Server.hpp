#ifndef R_TYPE_SERVER_HPP_
#define R_TYPE_SERVER_HPP_

#include "ControllerFactory.hh"
#include "DLManager.hh"
#include "NetworkHandler.hpp"

class ICondVar;
class IMutex;
class IThreadPool;
class ISocketFactory;
class ITimer;

class Server : public IObserver
{
protected:
  ICondVar *_cond;
  std::vector<Dictionary> _dic;
  DLManager _dlManager;
  ISocketFactory *_socketFactory;
  ControllerFactory _controllerFactory;
  IMutex *_mutex;
  NetworkHandler _network;
  IThreadPool *_pool;
  ITimer *_timer;
  bool _stop;
  ISocket *_test;
  bool _waiting;
public:
  Server(unsigned short port = 4242);
  virtual ~Server();
public:
  virtual bool game_test(unsigned short port, unsigned short time);
  virtual bool init();
  virtual bool run();
  virtual void stop(unsigned int);
  virtual void update(IObservable *, int status);
};

#endif //R_TYPE_SERVER_HPP_