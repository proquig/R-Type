#ifndef CLIENT_STATES_HH__
# define CLIENT_STATES_HH__

# include <InputPacket.hh>
# ifdef __linux__ 
#  include <unistd.h>
# elif _WIN32
#  include <windows.h>
# endif
# include <chrono>
# include <iostream>
# include <vector>
# include "graphicalController.hh"
# include "element.hh"
# include "DLManager.hh"
# include "IObserver.hpp"

# define Y_SPEED	10
# define X_SPEED	10
# define RTYPE_PORT_CLIENT 0
# define RTYPE_PORT_SERVER 8181
# define RTYPE_IP_SERVER "10.29.126.43"

class ICondVar;
class IMutex;
class ISocketFactory;
class ISocket;
class IThreadPool;
class ITimer;

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
	//Input
	uint16_t _input;
  std::vector<uint16_t> _inputQueue;
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
	WorkQueue<IPacket*> _paquetQueue;
	struct sockaddr _sockaddr;
	ISocketFactory *_socketFactory;
	ISocket *_socket;
	//Timer
	std::chrono::high_resolution_clock _clock;
	std::chrono::high_resolution_clock::time_point _ref;


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