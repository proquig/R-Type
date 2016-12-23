#ifndef WINDOW_HH__
# define WINDOW_HH__

# include "element.hh"
# include "workQueue.hh"
# include "coords.hh"
# include <iostream>
# include <thread>
# include <vector>

# define EVENT_TIMER	1000

class IObservable;

struct RType
{
	enum Key
	{
		NONE = 1 << 0,
		ENTER = 1 << 1,
		SPACE = 1 << 2,
		UP = 1 << 3,
		DOWN = 1 << 4,
		LEFT = 1 << 5,
		RIGHT = 1 << 6,
	};
};

struct Event
{
	enum Type {
		QUIT = 0,
		RESIZE,
		KEYPRESS,
		KEYRELEASE,
		CLICK
	};

	char	*name;
	RType::Key key;
	Type	type;
	Coords	*mouse;
	Coords	*size;

	Event(Type _type, RType::Key _key, char *_name, int _x, int _y, int _w, int _h)
		: type(_type), key(_key), name(_name), mouse(new Coords(_x, _y)), size(new Coords(_w, _h)) {}
};

class IWindow
{

public:

	virtual void	run(WorkQueue<AElement *> *, WorkQueue<Event *> *, IObservable* = nullptr) = 0;
	virtual void	pollEvent(void) = 0;
	virtual void	renderScene(void) = 0;
	virtual void	render(void) = 0;

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

	std::vector<AElement *>	scene;

	WorkQueue<AElement *>	*elementQueue;
	WorkQueue<Event *>		*eventQueue;

public:

	AWindow(int _w, int _h, std::string _name) : width(_w), height(_h), name(_name) {}

};

#endif /* !WINDOW_HH__ */