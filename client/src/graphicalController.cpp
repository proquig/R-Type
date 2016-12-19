#include "graphicalController.hh"
#include "SFMLWindow.hh"
#include "SFMLSprite.hh"
#include <thread>

GraphicalController::GraphicalController(GLib lib, int _w, int _h, std::string _n)
{
	switch (lib)
	{
	case SFML:

		this->window = new SFMLWindow(_w, _h, _n);
		this->windowQueue = new WorkQueue<AElement *>;
		this->eventQueue = new WorkQueue<Event *>;
		break;
	}
}

bool	GraphicalController::initAction(void)
{
	this->windowThread = new std::thread(&GraphicalController::windowAction, this);
	return (true);
}

void	GraphicalController::windowAction(void)
{
	std::cout << "Start Window ..." << std::endl;
	this->window->run(this->windowQueue, this->eventQueue);
}

void	GraphicalController::elementAction(AElement *element)
{
	this->windowQueue->push(element);
}

Event *		GraphicalController::eventAction(void)
{
	return this->eventQueue->pop();
}