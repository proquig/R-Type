#ifndef R_TYPE_SERVER_HPP_
#define R_TYPE_SERVER_HPP_

#include "DLManager.hh"
#include "NetworkHandler.hpp"

class ICondVar;
class IMutex;
class IThreadPool;
class ISocketFactory;

class Server
{
protected:
  ICondVar *_cond;
  std::pair<Dictionary, Dictionary> _dic;
  DLManager _dlManager;
  IMutex *_mutex;
  NetworkHandler _network;
  IThreadPool *_pool;
  bool _stop;
  ISocketFactory *_socketFactory;
  bool _waiting;
public:
  Server(unsigned short port = 4242);
  virtual ~Server();
public:
  virtual bool game_test(unsigned short port, unsigned short time);
  virtual bool init();
  virtual bool run();
  virtual void stop(unsigned int);
};

#endif //R_TYPE_SERVER_HPP_