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
# include "DLManager.hh"
#include "IObserver.hpp"

# define Y_SPEED	10
# define X_SPEED	10

class ICondVar;
class IMutex;
class ISocketFactory;
class ISocket;
class IThreadPool;

class ClientStates : public IObserver
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

	//Bool
	bool _init;
	bool _waiting;
	bool _stop;
	//DLLoader
	std::vector<Dictionary> _dic;
	DLManager _dlManager;
	//ThreadPool
	ICondVar *_cond;
	IMutex *_mutex;
	IThreadPool *_pool;
	//Network
	uint8_t game_id;
	uint8_t packet_id;
	ISocketFactory *_socketFactory;
	ISocket *_socket;

public:
	ClientStates();
	virtual ~ClientStates();

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
	virtual void update(IObservable*, int);
protected:
	bool init();
};


#endif /* !CLIENT_STATES_HH__ */