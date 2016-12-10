#pragma once

#include <functional>

class ICondVar;
class IMutex;
class Task;

class IThreadPool
{
public:
  virtual ~IThreadPool() = default;
public:
  virtual void addTask(Task *) = 0;
  virtual size_t init(void) = 0;
  virtual void stop(void) = 0;
  virtual ICondVar *createCondVar() = 0;
  virtual IMutex *createMutex() = 0;
  virtual Task *createTask(std::function<void(void)>) = 0;
  virtual void deleteCondVar(ICondVar *) = 0;
  virtual void deleteMutex(IMutex *) = 0;
};
