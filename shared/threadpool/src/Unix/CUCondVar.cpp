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
  {
    pthread_cond_wait(&_condVar, static_cast<CUMutex *>(mutex)->getMutex());
  }
}

void CUCondVar::wait(IMutex *mutex, unsigned long time)
{
  if (mutex)
  {
    if (time == 0)
      pthread_cond_wait(&_condVar, static_cast<CUMutex *>(mutex)->getMutex());
    else
    {
      struct timespec spec;

      clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &spec);
      spec.tv_sec += time / 1000;
      spec.tv_nsec += (time % 1000) * 1000000;
      if (spec.tv_nsec >= 1000000000L)
      {
        spec.tv_sec++;
        spec.tv_nsec = spec.tv_nsec - 1000000000L;
      }
      pthread_cond_timedwait(&_condVar, static_cast<CUMutex *>(mutex)->getMutex(), &spec);
    }
  }
}

void CUCondVar::signal()
{
  pthread_cond_signal(&_condVar);
}

void CUCondVar::broadcast()
{
  pthread_cond_broadcast(&_condVar);
}
