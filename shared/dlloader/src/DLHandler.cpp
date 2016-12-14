#include "ADLibrary.hh"
#include "DLHandler.hh"

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
  Dictionary dic;
  std::list<IDLibrary *>::iterator lib = libs.begin();

  while (lib != libs.end())
  {
    (*lib)->close();
    ADLibrary::deleteLibrary(*lib);
    lib = libs.erase(lib);
  }
  return (true);
}