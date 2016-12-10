#include "CUThread.hh"

static void *static_exec(void *userData)
{
  std::pair<std::function<void *(void *)>, void *> pair = (*static_cast<std::pair<std::function<void *(
      void *)>, void *> *>(userData));
  return pair.first(pair.second);
}

CUThread::CUThread(std::function<void *(void *)> function, void *param)
    : _arg(std::make_pair(function, param)), _exit(0), _exitcode(nullptr)
{
  pthread_create(&_thread, NULL, &static_exec, &_arg);
}

CUThread::~CUThread()
{
}

bool CUThread::startThread()
{
  return true;
}

bool CUThread::exitThread()
{
  _exit = INTERRUPT;
  pthread_exit(&_exit);
  return true;
}

bool CUThread::waitThisThread()
{
  return (pthread_join(_thread, &_exitcode) == 0);
}

bool CUThread::suspendThread()
{
  return true;
}

const int CUThread::getExitCode()
{
  if (!_exitcode)
    return 0;
  return *((int*)_exitcode);
}
