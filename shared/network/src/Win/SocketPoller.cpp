#include <thread>
#include "SocketPoller.hpp"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocketPoll.hpp"
#include "IThreadPool.hh"

WSAPOLLFD SocketPoller::_zero = { -1, 0, 0 };

SocketPoller::SocketPoller(IThreadPool *pool)
  : _cond(nullptr), _mutex(nullptr), _pool(nullptr), _stop(false)
{
  if (pool)
  {
    if ((_mutex = pool->createMutex()) == nullptr)
      return;
    if ((_cond = pool->createCondVar()) == nullptr)
    {
      pool->deleteMutex(_mutex);
      _mutex = nullptr;
      return;
    }
    _pool = pool;
    _pool->addTask(_pool->createTask(std::bind(&SocketPoller::run, this)));
  }
}

SocketPoller::~SocketPoller()
{
  if (_pool)
  {
    if (_mutex)
      _pool->deleteMutex(_mutex);
    if (_cond)
      _pool->deleteCondVar(_cond);
  }
}

void SocketPoller::add(ISocketPoll *socketPoll)
{
  short events = 0;
  int state = socketPoll->getState();

  _mutex->lock();
  _socketPolls.insert(_socketPolls.end(), socketPoll);
  _pollfds.insert(_pollfds.end(), _zero);
  _pollfds.front().fd = socketPoll->getFd();
  if (state & ISocketPoll::READ)
    events |= POLLIN;
  if (state & ISocketPoll::WRITE)
    events |= POLLOUT;
  _pollfds.front().events = events;
  _mutex->unlock();
}

IThreadPool *SocketPoller::getThreadpool()
{
  return _pool;
}

void SocketPoller::run()
{
  long idx;
  std::vector<WSAPOLLFD>::iterator pollfd;
  bool res;
  std::vector<ISocketPoll *>::iterator socketPoll;
  int status;

  _mutex->lock();
  if (_stop)
  {
    _mutex->unlock();
    return;
  }
  if (_socketPolls.size() != 0)
  {
    pollfd = _pollfds.begin();
    socketPoll = _socketPolls.begin();
    WSAPoll(&_pollfds.front(), _pollfds.size(), 1000);
    while (socketPoll != _socketPolls.end())
    {
      status = 0;
      if (pollfd->revents & POLLIN)
        status |= ISocketPoll::READ;
      if (pollfd->revents & POLLOUT)
        status |= ISocketPoll::WRITE;
      if (pollfd->revents & POLLERR || pollfd->revents & POLLHUP)
        status |= ISocketPoll::ERROR;
      idx = socketPoll - _socketPolls.begin();
      _mutex->unlock();
      if (status != 0)
        (*socketPoll)->notify(status);
      _mutex->lock();
      socketPoll = _socketPolls.begin() + idx;
      pollfd = _pollfds.begin() + idx;
      if (!update(socketPoll, pollfd))
      {
        pollfd = _pollfds.erase(pollfd);
        socketPoll = _socketPolls.erase(socketPoll);
      }
      else
      {
        ++pollfd;
        ++socketPoll;
      }
    }
  }
  else
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  _mutex->unlock();
  std::this_thread::sleep_for(std::chrono::milliseconds(10));
  if (!_stop)
    _pool->addTask(_pool->createTask(std::bind(&SocketPoller::run, this)));
}

void SocketPoller::stop()
{
  _mutex->lock();
  _stop = true;
  _mutex->unlock();
}

bool SocketPoller::update(std::vector<ISocketPoll *>::iterator socketPoll, std::vector<struct pollfd>::iterator pollfd)
{
  short events = 0;
  int state = (*socketPoll)->getState();

  if (state & ISocketPoll::CLOSE)
    return false;
  if (state & ISocketPoll::READ)
    events |= POLLIN;
  if (state & ISocketPoll::WRITE)
    events |= POLLOUT;
  (*pollfd).fd = (*socketPoll)->getFd();
  (*pollfd).events = events;
  return true;
}
