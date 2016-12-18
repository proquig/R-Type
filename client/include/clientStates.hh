#ifndef CLIENT_STATES_HH__
# define CLIENT_STATES_HH__

# ifdef __linux__ 
#  include <unistd.h>
# elif _WIN32
#  include <windows.h>
# endif
# include <iostream>
# include <vector>
# include "graphicalController.hh"
# include "InputPacket.hh"
# include "element.hh"

class ClientStates
{

	enum state
	{
		LAUNCH,
		MENU,
		GAME,
		SCORE,
		END,
		PREVIOUS
	};

	std::vector<state>	history;
	std::string			error;

	// Controllers
	GraphicalController	*controller;

	// Network
	uint8_t				game_id;
	uint8_t				packet_id;

public:

	bool			run(state);
	std::string		getErr(void) const;

	//////////////////////////////////////////
	// States
	//////////////////////////////////////////

	bool	launchState(void);
	bool	menuState(void);
	bool	gameState(void);
	bool	scoreState(void);
	bool	endState(void);

};


#endif /* !CLIENT_STATES_HH__ */