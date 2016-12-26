#include <iostream>
#include <sstream>
#include "Server.hpp"

bool safe_ushort(unsigned short &value, char *str)
{
  std::stringstream ss(str);

  ss >> value;
  return ss.eof();
}

int run(unsigned short tcp_port, unsigned short udp_port, unsigned short time)
{
  Server server(tcp_port);

  if (!server.init())
  {
    std::cerr << "Server init failed" << std::endl;
    return -1;
  }
  if (udp_port != 0 || time != 0)
    if (!server.game_test(udp_port, time))
    {
      std::cerr << "Server game test failed" << std::endl;
      return -1;
    }
  if (!server.run())
  {
    std::cerr << "Server run failed" << std::endl;
    return -1;
  }
  return 0;
}

int main(int ac, char **av)
{
  unsigned short
      tcp_port = 0,
      udp_port = 0,
      time = 0;

  if (ac < 2 || !safe_ushort(tcp_port, av[1]) || (ac >= 3 && !safe_ushort(udp_port, av[2])) || (ac >= 4 && !safe_ushort(time, av [3])))
  {
    std::cerr << "Usage : ./rtype_server [0-65535:tcp_port] [0-65535:udp_port] [0-65535:time]" << std::endl;
    std::cerr << "Required :" << std::endl;
    std::cerr << "  -- tcp_port : port for lobby listening socket (0 for random)" << std::endl;
    std::cerr << "Optional and only for debug :" << std::endl;
    std::cerr << "  -- udp_port : port for testing a game (0 for random)" << std::endl;
    std::cerr << "  -- time : timeout in seconds before exiting program (0 for infinite)" << std::endl;
    return (-1);
  }
  return (run(tcp_port, udp_port, time));
}
