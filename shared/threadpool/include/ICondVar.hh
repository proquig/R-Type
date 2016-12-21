#pragma once

#include	"IMutex.hh"

class ICondVar
{
public:
  virtual ~ICondVar() = default;
public:
  virtual void wait(IMutex*) = 0;
  virtual void wait(IMutex *, unsigned long) = 0;
  virtual void signal() = 0;
  virtual void broadcast() = 0;
};