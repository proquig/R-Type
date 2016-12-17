#include "DLDictionary.hh"
#include "SocketFactory.hpp"

ISocketFactory *instantiate(IThreadPool* pool)
{
  ISocketFactory *factory = new SocketFactory(pool);
  return factory;
}

void destroy(ISocketFactory *factory)
{
  if (factory)
    delete factory;
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
