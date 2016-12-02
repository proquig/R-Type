#include "DLException.hh"

DLException::DLException(std::string name, std::string error)
{
  _message = std::string("######################################\n");
  _message += std::string("##  Error on library : ");
  _message += name;
  _message += std::string("\n######################################\n");
  _message += error;
}

const char* DLException::what() const throw()
{
  return _message.c_str();
}