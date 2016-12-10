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
    SleepConditionVariableCS(&_condVar, static_cast<CWMutex*>(mutex)->getMutex(), INFINITE);
}

void CWCondVar::signal()
{
  WakeConditionVariable(&_condVar);
}

void CWCondVar::broadcast()
{
  WakeAllConditionVariable(&_condVar);
}
