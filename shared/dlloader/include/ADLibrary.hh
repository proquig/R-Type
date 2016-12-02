#ifndef R_TYPE_ADLIBRARY_HH_
#define R_TYPE_ADLIBRARY_HH_

#include "IDLibrary.hh"

class ADLibrary : public IDLibrary
{
protected:
  int _id;
  std::string _name;
  std::string _path;
public:
  ADLibrary(int id, std::string name, std::string path);
  virtual ~ADLibrary() = default;
public:
  static IDLibrary *createLibrary(int id, std::string name, std::string path);
  std::string getName() const;
};

#endif //R_TYPE_ADLIBRARY_HH_