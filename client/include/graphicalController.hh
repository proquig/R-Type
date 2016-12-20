#ifndef GRAPHICAL_CONTROLLER_HH__
# define GRAPHICAL_CONTROLLER_HH__

# include "Observable.hpp"
# include "workQueue.hh"
# include "window.hh"
# include "hookEvent.hh"
# include "coords.hh"
# include <thread>
# include <vector>

class GraphicalController : public Observable
{

	Coords					*windowSize;

	///////////////////////////////////////
	AWindow					*window;
	WorkQueue<AElement *>	*windowQueue;

	///////////////////////////////////////
	AHookEvent				*hooker;
	WorkQueue<Event *>		*eventQueue;

	std::thread				*windowThread;

	///////////////////////////////////////
	// std::vector<ASprite *>	ressources;
	std::vector<AElement *>		scene;


public:

	GraphicalController(GLib, int, int, std::string);

	bool	initAction(void);
	void	windowAction(void);
	void	elementAction(unsigned int, ElementType, int, int, int, int);
	Event	*eventAction(void);

};

#endif /* !GRAPHICAL_CONTROLLER_HH__ */