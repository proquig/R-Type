#include "graphicalController.hh"
#include "serializer.hh"
#include "element.hh"
#ifdef __linux__ 
# include <unistd.h>
#elif _WIN32
# include <windows.h>
#endif

int main(int ac, char **av)
{
	GraphicalController		controller(SFML, 800, 450, "R-type");
	clientUDP::Serializer	serializer(0, 0); // (gameId, magic)
	clientUDP::Packet		*packet;
	Event					*event = NULL;

	//////////////////////////////////////////////////////////////////////
	//	UNIT TEST
	controller.elementAction(ElementFactory::create(PLAYER, "cyan_stay", 0, 0, 50, 50));
	//////////////////////////////////////////////////////////////////////

	controller.initAction();
	while (!event || event->type != Event::QUIT) {

		// Check for events
		event = controller.eventAction();

		// Event received
		if (event && (packet = serializer.serializeEvent(event))) {

			// Unit Test [print event]
			std::cout << "[EVENT] " << packet->data << std::endl;

			// Required for the threads
			#ifdef __linux__ 
			sleep(20);
			#elif _WIN32
			Sleep(20);
			#endif
		}
	}

	return 0;
}
