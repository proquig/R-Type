#ifndef GRAPHICAL_CONTROLLER_HH__
# define GRAPHICAL_CONTROLLER_HH__

# ifdef __linux__ 
#  include <unistd.h>
# elif _WIN32
#  include <windows.h>
# endif
# include "Observable.hpp"
# include "workQueue.hh"
# include "window.hh"
# include "hookEvent.hh"
# include "coords.hh"
#include "Text.hh"
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

  void setProperty(IWindow::eProperty, bool);
	bool	initAction(void);
	void	windowAction(void);
	void	elementAction(unsigned int, RType::eType, int, int, float, int);
  	void	elementAction(unsigned int, RType::eType, int, int, float, int, ASprite* sprite);
	Event	*eventAction(void);
	void	addText(unsigned int, std::string);
	std::string	getIp(unsigned int);

};

#endif /* !GRAPHICAL_CONTROLLER_HH__ */