#include "graphicalController.hh"
#include "serializer.hh"
#ifdef __linux__ 
# include <unistd.h>
#elif _WIN32
# include <windows.h>
#endif

int main(int ac, char **av)
{
	GraphicalController		controller(SFML, 1600, 900, "R-type");
	Serializer				serializer;
	TMP_PACKET				*packet;
	Event					*event = NULL;

	controller.initAction();
	while (!event || event->type != Event::QUIT) {
		event = controller.eventAction();
		if (event && (packet = serializer.serializeEvent(event))) {
			std::cout << "[EVENT] " << packet->data << std::endl;
			#ifdef __linux__ 
			sleep(20);
			#elif _WIN32
			Sleep(20);
			#endif
		}
	}

	return 0;
}
