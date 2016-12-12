// threadpool.cpp : Defines the exported functions for the DLL application.
//

#include <iostream>
#include "ThreadPool.hh"
#include "Task.hh"
#if RT_WIN
  #include "CWThread.hh"
  #include "CWMutex.hh"
  #include "CWCondVar.hh"
#elif RT_UNIX
  #include "CUThread.hh"
  #include "CUMutex.hh"
  #include "CUCondVar.hh"
#endif

ThreadPool::ThreadPool(size_t size)
    : _condition(nullptr), _init(false), _size(size), _stop(false), _taskMutex(nullptr)
{
}

ThreadPool::~ThreadPool()
{
  if (_init)
  {
    if (_taskMutex && _condition)
      for (IThread *thread : _threads)
      {
        thread->waitThisThread();
        delete thread;
      }
    if (_taskMutex)
      deleteMutex(_taskMutex);
    if (_condition)
      deleteCondVar(_condition);
  }
}

size_t ThreadPool::init()
{
  IThread *thread;

  if (!_init)
  {
    _init = true;
    if ((_taskMutex = this->createMutex()) == nullptr)
      return size_t(-1);
    if ((_condition = this->createCondVar()) == nullptr)
      return size_t(-1);
    for (size_t i = 0; i != _size; ++i)
    {
#ifdef RT_WIN
      if ((thread = new CWThread(std::bind(&ThreadPool::exec, this, std::placeholders::_1))) != nullptr)
        _threads.push_back(thread);
#elif RT_UNIX
      if ((thread = new CUThread(std::bind(&ThreadPool::exec, this, std::placeholders::_1))) != nullptr)
        _threads.push_back(thread);
#endif
    }
    _size = _threads.size();
    return _size;
  }
  return size_t(-1);
}

#if RT_UNIX
void *ThreadPool::exec(void *)
#elif RT_WIN
DWORD WINAPI ThreadPool::exec(void*)
#endif
{
  while (!_stop)
  {
    _taskMutex->lock();
    while ((!_stop) && (_tasks.empty()))
      _condition->wait(_taskMutex);
    if (_stop)
    {
      _taskMutex->unlock();
      return 0;
    }
    Task *task = _tasks.front();
    _tasks.pop();
    _taskMutex->unlock();
    (*task)();
    delete task;
  }
  return (0);
}

void ThreadPool::addTask(Task *task)
{
  _tasks.push(task);
  _condition->signal();
}

void ThreadPool::stop()
{
  if (!_stop)
  {
    std::cout << "Stopping pool" << std::endl;
    _stop = true;
    _condition->broadcast();
  }
}

ICondVar *ThreadPool::createCondVar()
{
  ICondVar* condvar = nullptr;
#ifdef RT_WIN
  condvar = new CWCondVar();
#elif RT_UNIX
  condvar = new CUCondVar();
#endif
  return condvar;
}

IMutex *ThreadPool::createMutex()
{
  IMutex* mutex = nullptr;
#ifdef RT_WIN
  mutex = new CWMutex();
#elif RT_UNIX
  mutex = new CUMutex();
#endif
  return mutex;
}

Task *ThreadPool::createTask(std::function<void(void)> function)
{
  return new Task(function);
}

void ThreadPool::deleteCondVar(ICondVar *condvar)
{
  if (condvar)
    delete condvar;
}

void ThreadPool::deleteMutex(IMutex *mutex)
{
  if (mutex)
    delete mutex;
}
