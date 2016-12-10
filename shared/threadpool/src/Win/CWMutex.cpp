#include "CWMutex.hh"

CWMutex::CWMutex()
    : _init(false)
{
  init();
}

CWMutex::~CWMutex()
{
  destroy();
}

void CWMutex::destroy()
{
  if (_init)
    DeleteCriticalSection(&_mutex);
}

void CWMutex::init()
{
  InitializeCriticalSection(&_mutex);
  _init = true;
}

void CWMutex::lock()
{
  EnterCriticalSection(&_mutex);
}

void CWMutex::trylock()
{
  TryEnterCriticalSection(&_mutex);
}

void CWMutex::unlock()
{
  LeaveCriticalSection(&_mutex);
}

LPCRITICAL_SECTION CWMutex::getMutex()
{
  return &_mutex;
}
