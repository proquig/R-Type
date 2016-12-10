#pragma once

#include <Windows.h>
#include "CWMutex.hh"
#include "ICondVar.hh"

class CWCondVar : public ICondVar
{
private:
  bool _init;
  CONDITION_VARIABLE _condVar;
public:
  CWCondVar();
  virtual ~CWCondVar();
public:
  virtual void wait(IMutex *);
  virtual void signal();
  virtual void broadcast();
protected:
  virtual void destroy();
  virtual void init();
};

