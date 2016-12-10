#include "CWThread.hh"

static DWORD WINAPI static_exec(void *userData)
{
  std::pair<std::function<unsigned short(void *)>, void *> pair = (*static_cast<std::pair<std::function<unsigned short(
      void *)>, void *> *>(userData));
  return pair.first(pair.second);
}

CWThread::CWThread(std::function<unsigned short(void *)> function, void *param)
    : _arg(std::make_pair(function, param))
{
  if ((_thread = CreateThread(NULL, 0, static_exec, &_arg, CREATE_SUSPENDED, NULL)) == NULL)
    throw new std::exception("CreateThread error");
  ResumeThread(_thread);
}

CWThread::~CWThread()
{
}

bool CWThread::exitThread()
{
  return (TerminateThread(_thread, 0) != 0);
}

bool CWThread::waitThisThread()
{
  Sleep(5);
  WaitForSingleObject(_thread, INFINITE);
  return true;
}

bool CWThread::suspendThread()
{
  return (SuspendThread(_thread) != -1);
}

const int CWThread::getExitCode()
{
  DWORD code;
  GetExitCodeThread(_thread, &code);
  return code;
}
