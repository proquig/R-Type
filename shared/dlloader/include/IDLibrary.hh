#ifndef R_TYPE_IDLIBRARY_HH_
#define R_TYPE_IDLIBRARY_HH_

#include <string>
#include "DLDictionary.hh"

class IDLibrary
{
public:
  virtual ~IDLibrary() = default;
public:
  virtual std::string getName() const = 0;
  virtual bool load() = 0;
  virtual bool close() = 0;
  virtual Dictionary getDictionary() = 0;
};

#endif //R_TYPE_IDLIBRARY_HH_