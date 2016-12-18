#include "clientStates.hh"

int main(int ac, char **av)
{
	ClientStates	client;

	if (client.launchState())
		return 0;
	std::cerr << client.getErr() << std::endl;
	return 1;
}
