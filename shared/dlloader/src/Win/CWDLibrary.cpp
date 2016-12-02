#include "CWDLibrary.hh"

CWDLibrary::CWDLibrary(int id, std::string name, std::string path)
    : ADLibrary(id, name, path), _handler(nullptr)
{
}

bool CWDLibrary::load(void)
{
  return ((_handler = LoadLibrary(_path.c_str())) != NULL);
}

Dictionary CWDLibrary::getDictionary(void)
{
  GET_DICTIONARY getDict;

  if (!(getDict = (GET_DICTIONARY) GetProcAddress(_handler, DICTIONARY_GETTER)))
    return (NULL);
  return (getDict());
}

bool CWDLibrary::close(void)
{
  if (_handler)
    return (FreeLibrary(_handler));
  return true;
}
