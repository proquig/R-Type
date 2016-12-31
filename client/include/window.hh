#ifndef WINDOW_HH__
# define WINDOW_HH__

# include <iostream>
# include <thread>
# include <vector>
# include "RType.hpp"
# include "element.hh"
# include "workQueue.hh"
# include "coords.hh"

# define EVENT_TIMER	1000

class IObservable;

struct Event
{
	enum Type {
		QUIT = 0,
		RESIZE = 1,
		KEYPRESS = 2,
		KEYRELEASE = 3,
		CLICK = 4
	};

	char	*name;
	RType::eKey key;
	Type	type;
	Coords	*mouse;
	Coords	*size;

	Event(Type _type, RType::eKey _key, char *_name, int _x, int _y, int _w, int _h)
		: type(_type), key(_key), name(_name), mouse(new Coords(_x, _y)), size(new Coords(_w, _h)) {}
};

class IWindow
{
public:
	enum eProperty {
		KEY_REPEAT,
	};

	virtual void	run(WorkQueue<AElement*>*, WorkQueue<Event *> *, IObservable* = nullptr) = 0;
	virtual void	pollEvent(void) = 0;
	virtual void	render(void) = 0;
	virtual void setProperty(IWindow::eProperty, bool) = 0;

	/////////////////////////////////////////////////
	// GETTERS
	/////////////////////////////////////////////////

	virtual void *	getHandler(void) = 0;
	virtual int		getWidth(void) = 0;
	virtual int		getHeight(void) = 0;

};

class AWindow : public IWindow
{

protected:

	int						width;
	int						height;
	std::string				name;

	//std::vector<AElement *>	*scene;

	WorkQueue<AElement *>	*elementQueue;
	WorkQueue<Event *>		*eventQueue;
  	//Vec<AElement*>			*vec;
	std::vector<AElement*>	*scene;
public:

	AWindow(int _w, int _h, std::string _name) : width(_w), height(_h), name(_name) {}

};

#endif /* !WINDOW_HH__ */