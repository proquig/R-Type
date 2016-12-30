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

void GraphicalController::setProperty(IWindow::eProperty prop, bool flag)
{
  if (window)
    window->setProperty(prop, flag);
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
  std::vector<AElement *>::iterator			elem;
  bool										match = false;
  float										scale = 0.f;

#ifndef NDEBUG
	std::cout << "graphicalController:" << this->scene.size() << "workQ:" << windowQueue->getQueue().size()  <<std::endl;
#endif
	if (this->scene.size()) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ) {
			(*elem)->live();
            if ((*elem)->getTtl() <= 0  && (*elem)->getType() != RType::SET) {
				//delete (*elem);
				//       std::cout << "Delete -> TYPE:" << (*elem)->getType() << "\tID:" << (*elem)->getId() << std::endl;
                elem = this->scene.erase(elem);
            }else
				++elem;
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
	AElement									*element;

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

void	GraphicalController::elementAction(unsigned int id, RType::eType type, int x, int y, float angle, int speed, ASprite* sprite)
{
	std::vector<AElement *>::iterator			elem;
	bool										match = false;
	float										scale = 0.f;

	//std::cout << "graphicalController:" << this->scene.size() << std::endl;
	if (this->scene.size()) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ) {
			(*elem)->live();
            if ((*elem)->getTtl() <= 0  && (*elem)->getType() != RType::SET) {
				//delete (*elem);
				//       std::cout << "Delete -> TYPE:" << (*elem)->getType() << "\tID:" << (*elem)->getId() << std::endl;
                elem = this->scene.erase(elem);
            }else
				++elem;
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
		AElement									*element;

		element = ElementFactory::create(id, type);
	  	element->setSprite(sprite);
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

void		GraphicalController::addText(unsigned int id, std::string txt)
{
	std::vector<AElement *>::iterator elem;

	for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
		if ((*elem)->getId() == id) {
			((Text*)(*elem))->setString(txt);
		}
	}
}

std::string		GraphicalController::getIp(unsigned int id)
{
	std::vector<AElement *>::iterator elem;
	std::string ret;
	for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
		if ((*elem)->getId() == id) {
			//ret = ((Text*)(*elem))->getString();
			std::size_t pos = ret.find(" : ") + 4;

			std::string str3;
			ret = ret.substr(pos);
		}
	}
	return (ret);
}