#pragma once

#include <Windows.h>
#include "IMutex.hh"

class CWMutex : public IMutex
{
private:
  bool _init;
  CRITICAL_SECTION _mutex;
public:
  CWMutex();
  virtual ~CWMutex();
public:
  virtual void lock();
  virtual void trylock();
  virtual void unlock();
  LPCRITICAL_SECTION getMutex();
protected:
  virtual void destroy();
  virtual void init();
};

