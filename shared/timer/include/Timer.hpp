#ifndef R_TYPE_TIMER_HPP_
#define R_TYPE_TIMER_HPP_

#include <thread>
#include "ITimer.hpp"
#include "Observable.hpp"

class ICondVar;
class IMutex;
class IThreadPool;

class Timer : public ITimer, public Observable
{
protected:
  ICondVar *_cond;
  IMutex *_mutex;
  IThreadPool *_pool;
  bool _stop;
  unsigned int _timer;
  std::thread *_thread;
public:
  Timer(IThreadPool* = nullptr);
  virtual ~Timer() = default;
public:
  virtual void setTimer(unsigned int);
  virtual void stop();
protected:
  virtual void run();
};

#endif //R_TYPE_TIMER_HPP_