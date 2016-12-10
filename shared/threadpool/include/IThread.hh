#pragma once

class IThread
{
public:
  virtual ~IThread() = default;
public:
  virtual bool exitThread() = 0;
  virtual bool suspendThread() = 0;
  virtual bool waitThisThread() = 0;
  virtual const int getExitCode() = 0;
};
