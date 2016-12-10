#pragma once

#include <pthread.h>
#include "IMutex.hh"

class CUMutex : public IMutex
{
protected:
  bool _init;
  pthread_mutex_t _mutex;
public:
  CUMutex();
  virtual ~CUMutex();
public:
  virtual void lock();
  virtual void trylock();
  virtual void unlock();
  pthread_mutex_t *getMutex();
protected:
  virtual void destroy();
  virtual void init();
};
