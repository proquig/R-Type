#ifndef CWDLIBRARY_H__
#define CWDLIBRARY_H__

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>
#include "ADLibrary.hh"

class CWDLibrary : public ADLibrary
{
private:
  HMODULE _handler;
public:
  CWDLibrary(int id, std::string name, std::string path);
public:
  bool load(void);
  bool close(void);
  Dictionary getDictionary(void);
};

#endif /* !CWDLIBRARY_H__ */
