#include <iostream>
#include "Message.hpp"

int main(int ac, char **av)
{
  Message msg;
  std::vector<unsigned char> data;
  std::string delim("\n");
  if (ac < 3)
    return (-1);
  std::string str(av[1] + delim + av[2] + delim);
  data.insert(data.end(), str.begin(), str.end());
  std::cout << "Result of unserialize(" << av[1] << "\\n" << av[2] << "\\n" << ") : " << msg.unserialize(data) << std::endl;
  std::cout << "Msg :" << msg.getMsg() << std::endl;
  std::cout << "Param :" << msg.getParam() << std::endl;
  data = msg.serialize();
  std::string out(data.begin(), data.end());
  std::cout << "OUT :" << std::endl;
  std::cout << out << std::endl;
  return (0);
}
