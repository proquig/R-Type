#include "graphicalController.hh"
#include "SFMLWindow.hh"
#include "SFMLSprite.hh"
#include <thread>

GraphicalController::GraphicalController(GLib lib, int _w, int _h, std::string _n)
	: windowSize(new Coords(_w, _h))
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
	this->scene.clear();
	this->windowThread = new std::thread(&GraphicalController::windowAction, this);
	return (true);
}

void	GraphicalController::windowAction(void)
{
	this->window->run(this->windowQueue, this->eventQueue, this);
}

void	GraphicalController::elementAction(unsigned int id, ElementType type, int x, int y, int w, int h)
{
	AElement									*element;
	std::vector<AElement *>::const_iterator		elem;
	bool										match = false;

	if (this->scene.size()) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			if ((*elem)->getId() == id) {
				(*elem)->move(x, y);
				this->windowQueue->push(*elem);
				match = true;
			}
		}
	}
	if (!match) {
		element = ElementFactory::create(
			id, type, "CYAN_STAY",
			x, y, w, h
		);
		this->scene.push_back(element);
		this->windowQueue->push(element);
	}
}

Event *		GraphicalController::eventAction(void)
{
	return this->eventQueue->pop();
}