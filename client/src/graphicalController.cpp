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
	this->scene = std::vector<AElement *>();
	this->windowThread = new std::thread(&GraphicalController::windowAction, this);
	return (true);
}

void	GraphicalController::windowAction(void)
{
	this->window->run(this->windowQueue, this->eventQueue, this);
}

void	GraphicalController::elementAction(unsigned int id, ElementType type, int x, int y, float angle, int speed)
{
	AElement									*element;
	std::vector<AElement *>::const_iterator		elem;
	bool										match = false;
	float										scale = 0.f;

	if (this->scene.size()) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			if ((*elem)->getId() == id) {
				(*elem)->move(x, y, angle, speed);
				this->windowQueue->push(*elem);
				match = true;
			}
		}
	}
	if (!match) {
		element = ElementFactory::create(id, type);
		element->move(x, y, angle, speed);
		if (element->getType() == SET) {
			scale = (float)this->windowSize->y / 300;
			element->setScale(scale);
		}
		this->scene.push_back(element);
		this->windowQueue->push(element);
	}
}

Event *		GraphicalController::eventAction(void)
{
	return this->eventQueue->pop();
}