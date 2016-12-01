#include <iostream>
#include "DLibrary.hh"

#ifdef RT_UNIX
  #include "CUDLibrary.hh"
#elif RT_WIN
  #include "CWDLibrary.hh"
#endif

/////////////////////////////////////////////////////////
// DLFactory
/////////////////////////////////////////////////////////

IDLibrary *DLFactory::createLibrary(int _id, const char *_name, const char *_path)
{
  IDLibrary *library;

#ifdef RT_UNIX
  library = new CUDLibrary(_id, _name, _path);
#elif RT_WIN
  library = new CWDLibrary(_id, _name, _path);
#endif

  return (library);
}

/////////////////////////////////////////////////////////
// DLHandler
/////////////////////////////////////////////////////////

void DLHandler::add(IDLibrary *lib)
{
  this->libs.push_back(lib);
}

bool DLHandler::loadByName(std::string name)
{
  for (std::list<IDLibrary *>::const_iterator lib = this->libs.begin(); lib != libs.end(); ++lib)
  {
    if (name == (*lib)->getName())
      return ((*lib)->load());
  }
  return (false);
}

bool DLHandler::loadAll(std::string &err)
{
  for (std::list<IDLibrary *>::const_iterator lib = this->libs.begin(); lib != libs.end(); ++lib)
  {
    if (!(*lib)->load())
    {
      err = (*lib)->getName();
      return (false);
    }
  }
  return (true);
}

Dictionary DLHandler::getDictionaryByName(std::string name)
{
  for (std::list<IDLibrary *>::const_iterator lib = this->libs.begin(); lib != libs.end(); ++lib)
  {
    if (name == (*lib)->getName())
      return ((*lib)->getDictionary());
  }
  return (NULL);
}

bool DLHandler::closeList(void)
{
  for (std::list<IDLibrary *>::const_iterator lib = this->libs.begin(); lib != libs.end(); ++lib)
  {
    (*lib)->close();
  }
  return (true);
}

/////////////////////////////////////////////////////////
// DLManager
/////////////////////////////////////////////////////////

void DLManager::add(int _id, const char *_name, const char *_path)
{
  IDLibrary *lib;

  lib = this->factory.createLibrary(_id, _name, _path);
  this->handler.add(lib);
}