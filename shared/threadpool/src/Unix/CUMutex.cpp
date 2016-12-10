#include "CUMutex.hh"

CUMutex::CUMutex()
    : _init(false)
{
  init();
}

CUMutex::~CUMutex()
{
  destroy();
}

void CUMutex::destroy()
{
  if (_init)
    pthread_mutex_destroy(&_mutex);
}

void CUMutex::init()
{
  pthread_mutex_init(&_mutex, NULL);
  _init = true;
}

void CUMutex::lock()
{
  pthread_mutex_lock(&_mutex);
}

void CUMutex::trylock()
{
  pthread_mutex_trylock(&_mutex);
}

void CUMutex::unlock()
{
  pthread_mutex_unlock(&_mutex);
}

pthread_mutex_t *CUMutex::getMutex()
{
  return &_mutex;
}
