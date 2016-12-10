#include "CUCondVar.hh"
#include "CUMutex.hh"

CUCondVar::CUCondVar()
    : _init(false)
{
  init();
}

CUCondVar::~CUCondVar()
{
  destroy();
}

void CUCondVar::destroy()
{
  if (_init)
    pthread_cond_destroy(&_condVar);
}

void CUCondVar::init()
{
  pthread_cond_init(&_condVar, NULL);
  _init = true;
}

void CUCondVar::wait(IMutex *mutex)
{
  if (mutex)
    pthread_cond_wait(&_condVar, static_cast<CUMutex *>(mutex)->getMutex());
}

void CUCondVar::signal()
{
  pthread_cond_signal(&_condVar);
}

void CUCondVar::broadcast()
{
  pthread_cond_broadcast(&_condVar);
}
