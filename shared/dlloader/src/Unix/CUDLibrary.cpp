#include <dlfcn.h>
#include "CUDLibrary.hh"

CUDLibrary::CUDLibrary(int id, std::string name, std::string path)
    : ADLibrary(id, name, path), _handler(nullptr)
{
}

bool CUDLibrary::load(void)
{
  return ((this->_handler = dlopen(_path.c_str(), RTLD_LAZY)) != NULL);
}

Dictionary CUDLibrary::getDictionary(void)
{
  GET_DICTIONARY getDict;

  if (!(getDict = (GET_DICTIONARY) dlsym(_handler, DICTIONARY_GETTER)))
    return (NULL);
  return (getDict());
}

bool CUDLibrary::close(void)
{
  if (_handler)
    return (dlclose(_handler) == 0);
  return true;
}
