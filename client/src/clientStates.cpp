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
	case TEST: return this->testState();
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
	
	// [TO-DO NETWORK] CONNECT TO SERVER
	this->game_id	= 0;
	this->packet_id = 0;

	while (!event || event->type != Event::QUIT) {

		// [TO-DO NETWORK] RECEIVE GameDataPacket FROM NETWORK

		// [TO-DO SERIALISATION] unserialize it and get id_element, x, y
		// [TO-DO SERIALISATION] Implement type, width, height
		// [TO-DO GRAPHICAL] Remove skin from factory and make it auto.

		/*
		this->controller->elementAction(
			ElementFactory::create(
				[id_element], PLAYER, "CYAN_STAY",
				[x], [y], [width], [height]
			)
		);
		*/

		// Check for events
		event = this->controller->eventAction();

		// Event received
		if (event) {

			// SERIALIZE EVENT
			eventPacket.setHeader(
				IPacket::INPUT_DATA, IPacket::ACK_NEED,
				MAGIC, this->game_id,
				this->packet_id, 4242, 0
			);
			eventPacket.putInput(event->type);
			serializedEvent = eventPacket.serialize();

			// [TO-DO NETWORK] Send std::string serializedEvent to server

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


/////////////////////////////////////////////////////////////////////////////////////////
// UNIT_TEST
/////////////////////////////////////////////////////////////////////////////////////////

bool	ClientStates::testState(void)
{
	Event			*event = NULL;
	Coords			*player = new Coords(200, 20);
	Coords			*windowSize = new Coords(800, 450);

	std::cout << "=================================" << std::endl;
	std::cout << "============  TEST  =============" << std::endl;
	std::cout << "=================================" << std::endl << std::endl;

	this->controller = new GraphicalController(SFML, windowSize->x, windowSize->y, "R-type - Graphical tests");
	this->controller->initAction();

	/*
	this->controller->elementAction(
		ElementFactory::create(
			1, SET, "WASTE_LAND",
			0, 0, windowSize->x, windowSize->y
		)
	);
	*/

	while (!event || event->type != Event::QUIT) {
		if (event = this->controller->eventAction()) {
			switch (event->type) {
				case Event::UP: player->y -= Y_SPEED; break;
				case Event::DOWN: player->y += Y_SPEED; break;
				case Event::RIGHT: player->x += X_SPEED; break;
				case Event::LEFT: player->x -= X_SPEED; break;
				case Event::RESIZE: windowSize = event->size; break;
				default: break;
			}

			/*
			if (player->x < 0)
				player->x = 0;
			if (player->x > windowSize->x)
				player->x = windowSize->x;
			if (player->y < 0)
				player->y = 0;
			if (player->y > windowSize->y)
				player->y = windowSize->y;

				*/
			this->controller->elementAction(
				ElementFactory::create(
					1, PLAYER, "CYAN_STAY",// + std::string(event->name),
					player->x, player->y, 300, 200
				)
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
