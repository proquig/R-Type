#include	"CWCondVar.hh"

CWCondVar::CWCondVar()
    : _init(false)
{
  init();
}

CWCondVar::~CWCondVar()
{
  destroy();
}

void CWCondVar::destroy()
{
}

void CWCondVar::init()
{
  InitializeConditionVariable(&_condVar);
  _init = true;
}

void CWCondVar::wait(IMutex *mutex)
{
  if (mutex)
  {
    SleepConditionVariableCS(&_condVar, static_cast<CWMutex *>(mutex)->getMutex(), INFINITE);
  }
}

void CWCondVar::wait(IMutex *mutex, unsigned long time)
{
  if (mutex)
  {
    if (time == 0)
      SleepConditionVariableCS(&_condVar, static_cast<CWMutex *>(mutex)->getMutex(), INFINITE);
    else
      SleepConditionVariableCS(&_condVar, static_cast<CWMutex *>(mutex)->getMutex(), time);
  }
}

void CWCondVar::signal()
{
  WakeConditionVariable(&_condVar);
}

void CWCondVar::broadcast()
{
  WakeAllConditionVariable(&_condVar);
}
