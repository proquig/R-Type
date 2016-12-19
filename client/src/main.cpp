#include "clientStates.hh"

int main(int ac, char **av)
{
	ClientStates			client;
	ClientStates::state		mode = ClientStates::LAUNCH;

	for (int i = 0; i < ac - 1; ++i) {
		if (std::string(av[i]) == "-m" && std::string(av[i + 1]) == "TEST")
			mode = ClientStates::TEST;
	}
	if (client.run(mode))
		return 0;
	std::cerr << client.getErr() << std::endl;
	return 1;
}
