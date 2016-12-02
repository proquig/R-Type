#include <iostream>
#include "ADLibrary.hh"

int main(int ac, char **av)
{
  IDLibrary *lib = ADLibrary::createLibrary(0, "threadpool", "threadpool.dll");
  std::cout << "lib->load()=" << (bool) lib->load() << std::endl;
  Dictionary dic = lib->getDictionary();
  if (dic != NULL && !dic->empty())
  {
    for (std::map<std::string, void *>::iterator sit = dic->begin(); sit != dic->end(); sit++)
      std::cout << "key=" << sit->first.c_str() << std::endl;
  }
  else
    std::cout << "dic empty" << std::endl;
  return 0;
}