#pragma once

#include <functional>

class Task
{
private:
  std::function<void()> _function;
public:
  Task(std::function<void()>);
  virtual ~Task();
public:
  void operator()();
};
