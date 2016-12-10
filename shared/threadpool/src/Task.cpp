#include "Task.hh"

Task::Task(std::function<void()> function)
    : _function(function)
{
}

Task::~Task()
{
}

void Task::operator()()
{
  _function();
}
