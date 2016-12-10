#include "DLDictionary.hh"
#include "ThreadPool.hh"

IThreadPool *instantiate(int nb)
{
  IThreadPool *threadpool = new ThreadPool(nb);
  return threadpool;
}

void destroy(IThreadPool *pool)
{
  if (pool)
    delete pool;
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
