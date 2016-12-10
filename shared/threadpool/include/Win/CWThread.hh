#pragma once

#include <functional>
#include <Windows.h>
#include "IThread.hh"

class CWThread : public IThread
{
private:
  std::pair<std::function<unsigned short(void*)>, void *> _arg;
  HANDLE _thread;
public:
  CWThread(std::function<unsigned short(void*)>, void * = nullptr);
  virtual ~CWThread();
public:
  virtual bool exitThread();
  virtual bool suspendThread();
  virtual bool waitThisThread();
  virtual const int getExitCode();
};
