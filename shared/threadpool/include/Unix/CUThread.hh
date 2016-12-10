#pragma once

#include <functional>
#include <pthread.h>
#include "IThread.hh"

#define INTERRUPT 42

class CUThread : public IThread
{
protected:
  std::pair<std::function<void*(void*)>, void *> _arg;
  int _exit;
  void* _exitcode;
  pthread_t _thread;
public:
  CUThread(std::function<void*(void*)>, void* = nullptr);
  virtual ~CUThread();
public:
  virtual bool startThread();
  virtual bool exitThread();
  virtual bool waitThisThread();
  virtual bool suspendThread();
  virtual const int getExitCode();
};
