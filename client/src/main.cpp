#include "clientStates.hh"

int main(int ac, char **av)
{
  ClientStates client;
  ClientStates::state mode = ClientStates::TEST;

  for (int i = 1; i < ac; ++i)
  {
    std::string flags(av[i]);
    if (flags[0] == '-' && flags.erase(flags.begin()) != flags.end())
      for (char c : flags)
        switch (c)
        {
          case 'm':
            if (i < ac - 1)
            {
              ++i;
              std::string mode_str(av[i]);
              if (mode_str.compare("TEST") == 0)
                mode = ClientStates::TEST;
              else if (mode_str.compare("LAUNCH") == 0)
                mode = ClientStates::LAUNCH;
            }
            break;
          default:
            std::cerr << "Unknown option or wrong format on flag" << c << std::endl;
        }
  }
  if (client.run(mode))
    return 0;
  std::cerr << client.getErr() << std::endl;
  return 1;
}
