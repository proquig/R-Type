#include "DLManager.hh"
#include "ADLibrary.hh"

void DLManager::add(int id, std::string name, std::string path)
{
  IDLibrary *lib;

  lib = ADLibrary::createLibrary(id, name, path);
  this->handler.add(lib);
}