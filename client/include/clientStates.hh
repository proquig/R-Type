#ifndef CLIENT_STATES_HH__
# define CLIENT_STATES_HH__

# include <InputPacket.hh>
# ifdef __linux__ 
#  include <unistd.h>
# elif _WIN32
#  include <windows.h>
# endif
# include <iostream>
# include <vector>
# include "graphicalController.hh"
# include "element.hh"

# define Y_SPEED	10
# define X_SPEED	10

class ClientStates
{

public:

	enum state
	{
		TEST,
		LAUNCH,
		MENU,
		GAME,
		SCORE,
		END,
		PREVIOUS
	};

private:

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
	bool	testState(void);

};


#endif /* !CLIENT_STATES_HH__ */