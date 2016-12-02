#ifndef R_TYPE_DLDICTIONARY_HH_
#define R_TYPE_DLDICTIONARY_HH_

#include <map>

#define DICTIONARY_GETTER  "getDictionary"

typedef std::map<std::string, void *> *Dictionary;

// Get Dictionary Function
#ifdef RT_UNIX
  typedef Dictionary  (*GET_DICTIONARY)(void);
#elif RT_WIN
  typedef __declspec(dllimport) Dictionary	(__cdecl *GET_DICTIONARY)(void);
#endif

#endif //R_TYPE_DLDICTIONARY_HH_