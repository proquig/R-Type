#include "ADLibrary.hh"

#ifdef RT_UNIX
  #include "CUDLibrary.hh"
#elif RT_WIN
  #include "CWDLibrary.hh"
#endif

ADLibrary::ADLibrary(int id, std::string name, std::string path)
    : _id(id), _name(name), _path(path)
{
  if (_path == std::string(""))
#ifdef RT_UNIX
    _path = std::string("./lib" + _name + ".so");
#elif RT_WIN
    _path = std::string(_name + ".dll");
#endif
}

IDLibrary* ADLibrary::createLibrary(int id, std::string name, std::string path)
{
#ifdef RT_UNIX
  return(new CUDLibrary(id, name, path));
#elif RT_WIN
  return(new CWDLibrary(id, name, path));
#endif
}

void ADLibrary::deleteLibrary(IDLibrary *lib)
{
  if (lib)
    delete lib;
}
std::string ADLibrary::getName() const
{
  return (this->_name);
}
