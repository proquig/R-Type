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
# include "Text.hh"
# include "Score.hh"
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

	int							score;
	AElement*					score_elem;

public:

	GraphicalController(GLib, int, int, std::string);

  void setProperty(IWindow::eProperty, bool);
	bool	initAction(void);
	void	windowAction(void);
	void	scoreAction(int);
	void	elementAction(unsigned int, RType::eType, int, int, float, int);
  	void	elementAction(unsigned int, RType::eType, int, int, float, int, ASprite* sprite);
	Event	*eventAction(void);
	void	setText(unsigned int, std::string);
	void	addText(unsigned int, std::string);
	void	rmText(unsigned int);
	std::string	getIp(unsigned int);
	bool	checkIp(std::string);

};

#endif /* !GRAPHICAL_CONTROLLER_HH__ */