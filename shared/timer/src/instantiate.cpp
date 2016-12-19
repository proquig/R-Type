#include "DLDictionary.hh"
#include "Timer.hpp"

ITimer *instantiate(IThreadPool* pool)
{
  return new Timer(pool);

}

void destroy(ITimer *timer)
{
  if (timer)
    delete timer;
}

extern "C" {
#ifdef RT_UNIX
Dictionary getDictionary(void)
#elif RT_WIN
__declspec(dllexport) Dictionary	__cdecl getDictionary(void)
#endif
{
  Dictionary dict = new std::map<std::string, void *>;
  (*dict)["instantiate"] = (void *) &instantiate;
  (*dict)["destroy"] = (void *) &destroy;
  return (dict);
}
}
