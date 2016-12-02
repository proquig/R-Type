#ifndef R_TYPE_DLMANAGER_HH_
#define R_TYPE_DLMANAGER_HH_

#include <string>
#include "DLHandler.hh"

class DLManager
{
public:
  DLHandler handler;
  void add(int id, std::string name, std::string path);
};

#endif //R_TYPE_DLMANAGER_HH_