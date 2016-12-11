#ifndef GRAPHICAL_CONTROLLER_HH__
# define GRAPHICAL_CONTROLLER_HH__

# include "workQueue.hh"
# include "window.hh"
# include "hookEvent.hh"
# include <thread>
# include <vector>

enum GLib
{
	SFML
};

class GraphicalController
{

	///////////////////////////////////////
	AWindow					*window;
	WorkQueue<AElement *>	*windowQueue;

	///////////////////////////////////////
	AHookEvent				*hooker;
	WorkQueue<Event *>		*eventQueue;

	std::thread				*windowThread;

	///////////////////////////////////////
	std::vector<ASprite *>	ressources;

public:

	GraphicalController(GLib, int, int, std::string);

	bool	initAction(void);
	void	windowAction(void);
	void	elementAction(AElement *);
	Event	*eventAction(void);

};

#endif /* !GRAPHICAL_CONTROLLER_HH__ */