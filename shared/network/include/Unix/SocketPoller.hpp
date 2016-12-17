#ifndef R_TYPE_SOCKETPOLLER_HPP_
#define R_TYPE_SOCKETPOLLER_HPP_

#include <map>
#include <poll.h>
#include <vector>
#include "ISocketPoll.hpp"

class ICondVar;
class IMutex;
class IThreadPool;

class SocketPoller
{
protected:
  ICondVar *_cond;
  IMutex *_mutex;
  IThreadPool *_pool;
  std::vector<struct pollfd> _pollfds;
  std::vector<ISocketPoll*> _socketPolls;
  bool _stop;
  static struct pollfd _zero;
public:
  SocketPoller(IThreadPool *);
  virtual ~SocketPoller();
public:
  virtual void add(ISocketPoll*);
  virtual IThreadPool* getThreadpool();
  virtual void run();
  virtual void stop();
private:
  virtual bool update(std::vector<ISocketPoll *>::iterator socketPoll, std::vector<struct pollfd>::iterator pollfd);
};

#endif //R_TYPE_SOCKETPOLLER_HPP_