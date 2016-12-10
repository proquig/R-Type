#pragma once

#include <vector>
#include <queue>
#if RT_WIN
  #include <Windows.h>
#endif
#include "IThreadPool.hh"

class IThread;

class ThreadPool : public IThreadPool
{
private:
  ICondVar *_condition;
  bool _init;
  size_t _size;
  bool _stop;
  IMutex *_taskMutex;
  std::queue<Task *> _tasks;
  std::vector<IThread *> _threads;
public:
  ThreadPool(size_t);
  virtual ~ThreadPool();
public:
  virtual size_t init();
  virtual void addTask(Task *);
  virtual void stop();
  virtual ICondVar *createCondVar();
  virtual IMutex *createMutex();
  virtual Task *createTask(std::function<void (void)>);
  virtual void deleteCondVar(ICondVar*);
  virtual void deleteMutex(IMutex*);
private:
#ifdef RT_UNIX
  virtual void* exec(void*);
#elif RT_WIN
  virtual DWORD WINAPI exec(void*);
#endif
};

