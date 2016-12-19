#include <thread>
#include "Timer.hpp"
#include "IThreadPool.hh"

Timer::Timer(IThreadPool *pool)
    : _pool(pool), _stop(false)
{
}

void Timer::addObserver(IObserver *o)
{
  Observable::addObserver(o);
  if (_collectionObserver.size() == 1 && _pool)
    _pool->addTask(_pool->createTask(std::bind(&Timer::update, this, _timer)));
}

void Timer::setTimer(unsigned int timer)
{
  if (timer > 5)
    _timer = timer;
}

void Timer::stop()
{
  _stop = true;
}

void Timer::update(unsigned int timer)
{
  if (_stop)
    return;
  std::this_thread::sleep_for(std::chrono::milliseconds(timer));
  notify(timer);
  if (_collectionObserver.size() >= 1 && _pool)
    _pool->addTask(_pool->createTask(std::bind(&Timer::update, this, _timer)));
}
