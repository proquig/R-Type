#include "ADLibrary.hh"

#if RT_UNIX
  #include "CUDLibrary.hh"
#elif RT_WIN
  #include "CWDLibrary.hh"
#endif

ADLibrary::ADLibrary(int id, std::string name, std::string path)
    : _id(id), _name(name), _path(path)
{
}

IDLibrary* ADLibrary::createLibrary(int id, std::string name, std::string path)
{
#ifdef RT_UNIX
  return(new CUDLibrary(id, name, path));
#elif RT_WIN
  return(new CWDLibrary(id, name, path));
#endif
}

std::string ADLibrary::getName() const
{
  return (this->_name);
}