#ifndef R_TYPE_DLHANDLER_HH_
#define R_TYPE_DLHANDLER_HH_

#include <list>
#include "IDLibrary.hh"

class DLHandler
{
private:
  std::list<IDLibrary *> libs;
public:
  void add(IDLibrary *);

  // LOAD
  bool loadByName(std::string);
  bool loadAll(std::string &);

  // GET DICTIONNARY
  Dictionary getDictionaryByName(std::string);

  // CLOSE
  bool closeList(void);
};
#endif //R_TYPE_DLHANDLER_HH_