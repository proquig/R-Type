#include "SFMLWindow.hh"

int main(int ac, char **av)
{
	AWindow		*window = new SFMLWindow(800, 600, "R-Type");

	window->init();
	return 0;
}
