#include <iostream>
#include <thread>
#include "Timer.hpp"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "IThreadPool.hh"

Timer::Timer(IThreadPool *pool)
    : _cond(nullptr), _mutex(nullptr), _pool(pool),
    _stop(true), _timer(10), _thread(nullptr)
{
  if (_pool)
  {
    _cond = _pool->createCondVar();
    _mutex = _pool->createMutex();
    _stop = false;
    _thread = new std::thread(&Timer::run, this);
  }
}

void Timer::setTimer(unsigned int timer)
{
  if (timer > 5)
    _timer = timer;
}

void Timer::stop()
{
  if (!_stop)
  {
    _stop = true;
    _thread->join();
  }
}

void Timer::run()
{
  _mutex->lock();
  while (!_stop)
  {
    _cond->wait(_mutex, _timer);
    if (_collectionObserver.size() != 0)
      notify(_timer);
  }
  _mutex->unlock();
}
