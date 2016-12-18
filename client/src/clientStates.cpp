#include "clientStates.hh"

bool	ClientStates::run(state to)
{
	this->error = "Unknown error.";
	if (PREVIOUS == to) {
		if (this->history.size() <= 1) {
			this->error = "Client states : No previous state.";
			return (false);
		}
		this->history.pop_back();
	}
	else
		this->history.push_back(to);
	switch (to) {
	case LAUNCH: return this->launchState();
		break;
	case MENU: return this->menuState();
		break;
	case GAME: return this->gameState();
		break;
	case SCORE: return this->scoreState();
		break;
	case END: return this->endState();
		break;
	default: return false;
		break;
	}
	return false;
}

std::string	ClientStates::getErr(void) const
{
	return this->error;
}

//////////////////////////////////////////
// States
//////////////////////////////////////////

bool	ClientStates::launchState(void)
{
	this->controller	= new GraphicalController(SFML, 800, 450, "R-type");

	this->controller->initAction();
	return this->run(MENU);
}

bool	ClientStates::menuState(void)
{
	std::cout << "Menu ..." << std::endl;
	return this->run(GAME);
}

bool		ClientStates::gameState(void)
{
	Event			*event = NULL;
	InputPacket		eventPacket;
	std::string		serializedEvent;
	
	// CONNECT TO SERVER
	this->game_id	= 0;
	this->packet_id = 0;

	// RECEIVE FROM NETWORK
	this->controller->elementAction(
		ElementFactory::create(
			1, PLAYER, "cyan_stay",
			0, 0, 50, 50
		)
	);

	while (!event || event->type != Event::QUIT) {

		// Check for events
		event = this->controller->eventAction();

		// Event received
		if (event) {

			// SERIALIZE EVENT
			eventPacket.putInput(event->type);
			serializedEvent = eventPacket.serialize();
			eventPacket.setHeader(
				IPacket::INPUT_DATA, IPacket::ACK_NEED,
				MAGIC, this->game_id,
				this->packet_id, serializedEvent.size(), 0
			);

			// Required for the threads
			#ifdef __linux__ 
				sleep(20);
			#elif _WIN32
				Sleep(20);
			#endif
		}
	}
	return true;
}

bool	ClientStates::scoreState(void)
{
	return true;
}

bool	ClientStates::endState(void)
{
	std::cout << "Bye Bye !" << std::endl;
	return true;
}
