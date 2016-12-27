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

void	GraphicalController::elementAction(unsigned int id, RType::eType type, int x, int y, float angle, int speed)
{
	AElement									*element;
	std::vector<AElement *>::iterator			elem;
	bool										match = false;
	float										scale = 0.f;

	if (this->scene.size()) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			(*elem)->live();
			if ((*elem)->getTtl() <= 0) {
				this->scene.erase(elem);
				elem = this->scene.begin();
			}
		}
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			if ((*elem)->getId() == id) {
				(*elem)->alive();
				if ((*elem)->getType() == RType::SET) {
					scale = (float)this->windowSize->y / 300;
					(*elem)->setScale(scale);
				}
				else
					(*elem)->move(x, y, angle, std::chrono::milliseconds(speed));
				this->windowQueue->push(*elem);
				match = true;
			}
		}
	}
	if (!match) {
		element = ElementFactory::create(id, type);
		element->setCoords(new Coords(x, y));
		element->setAngle(angle);
		element->setSpeed(std::chrono::milliseconds(speed));
		if (element->getType() == RType::SET) {
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