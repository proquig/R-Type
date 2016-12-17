#ifndef R_TYPE_SOCKETPOLLER_HPP_
#define R_TYPE_SOCKETPOLLER_HPP_

#include <vector>
#include <WinSock2.h>

class ICondVar;
class IMutex;
class ISocketPoll;
class IThreadPool;

class SocketPoller
{
protected:
  ICondVar *_cond;
  IMutex *_mutex;
  IThreadPool *_pool;
  std::vector<WSAPOLLFD> _pollfds;
  std::vector<ISocketPoll*> _socketPolls;
  bool _stop;
  static WSAPOLLFD _zero;
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