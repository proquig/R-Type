#ifndef CUDLIBRARY_H__
# define CUDLIBRARY_H__

#include "ADLibrary.hh"

class CUDLibrary : public ADLibrary
{
private:
  void *_handler;
public:
  CUDLibrary(int id, std::string name, std::string path);
public:
  bool load(void);
  bool close(void);
  Dictionary getDictionary(void);
};

#endif /* !CUDLIBRARY_H__ */
