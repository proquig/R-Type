#pragma once

#include <pthread.h>
#include "ICondVar.hh"

class CUCondVar : public ICondVar
{
protected:
  bool _init;
  pthread_cond_t	_condVar;
public:
  CUCondVar();
  virtual ~CUCondVar();
public:
  virtual void wait(IMutex*);
  virtual void wait(IMutex *, unsigned long);
  virtual void signal();
  virtual void broadcast();
protected:
  virtual void destroy();
  virtual void init();
};
