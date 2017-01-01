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
# include "ICondVar.hh"
# include "IMutex.hh"

class GraphicalController : public Observable
{

	Coords					*windowSize;

	///////////////////////////////////////
	AWindow					*window;
	WorkQueue<AElement *>	*windowQueue;
  	std::vector<AElement *>	*oldWindowQueue;


  ///////////////////////////////////////
	AHookEvent				*hooker;
	WorkQueue<Event *>		*eventQueue;

	std::thread				*windowThread;

  	//Vec<AElement*>			vec;

	///////////////////////////////////////
	// std::vector<ASprite *>	ressources;

	int							score;
	AElement*					score_elem;

public:

  GraphicalController(GLib, int, int, std::string);

  void setProperty(IWindow::eProperty, bool);
	bool	initAction(void);
	void	windowAction(void);
	void	scoreAction(int);
  	AElement	*elementAction(unsigned int, RType::eType, int, int, float, int, ASprite* sprite = nullptr);
	Event	*eventAction(void);
	bool	checkIp(std::string);
  	void 	resetScene();
  	//void	addMutex(IMutex* mutex);
  void removeElement(AElement *element);
};

#endif /* !GRAPHICAL_CONTROLLER_HH__ */