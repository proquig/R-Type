#include "DLManager.hh"
#include "ADLibrary.hh"

bool DLManager::add(int id, std::string name, std::string path)
{
  IDLibrary *lib;

  if ((lib = ADLibrary::createLibrary(id, name, path)) == nullptr)
    return false;
  this->handler.add(lib);
  return true;
}