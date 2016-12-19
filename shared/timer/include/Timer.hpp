#ifndef R_TYPE_TIMER_HPP_
#define R_TYPE_TIMER_HPP_

#include "ITimer.hpp"
#include "Observable.hpp"

class IThreadPool;

class Timer : public ITimer, public Observable
{
protected:
  IThreadPool *_pool;
  bool _stop;
  unsigned int _timer;
public:
  Timer(IThreadPool* = nullptr);
  virtual ~Timer() = default;
public:
  virtual void addObserver(IObserver*);
  virtual void setTimer(unsigned int);
  virtual void stop();
protected:
  virtual void update(unsigned int);
};

#endif //R_TYPE_TIMER_HPP_