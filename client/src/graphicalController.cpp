#include "graphicalController.hh"
#include "SFMLWindow.hh"
#include "SFMLSprite.hh"
#include <thread>
#include <sstream>
#include <ICondVar.hh>

GraphicalController::GraphicalController(GLib lib, int _w, int _h, std::string _n)
	: windowSize(new Coords(_w, _h)), score_elem(nullptr), score(-1), oldWindowQueue(nullptr)
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

bool	GraphicalController::initAction()
{
	this->score = -1;
	this->windowThread = new std::thread(&GraphicalController::windowAction, this);
	return (true);
}

void	GraphicalController::windowAction(void)
{
	this->window->run(this->windowQueue, this->eventQueue, this);
}

void 	GraphicalController::resetScene()
{
  this->windowQueue->lock();
  if (this->oldWindowQueue)
  {
	for (AElement *element : *this->oldWindowQueue)
	  if (element->getId())
		delete element;
	delete this->oldWindowQueue;
  }
  this->windowQueue->unlock();
  this->oldWindowQueue = this->windowQueue->popAll();
  for (AElement* element : *this->oldWindowQueue)
	if (element->getId())
	  this->windowQueue->remove(element);
}

AElement*	GraphicalController::elementAction(unsigned int id, RType::eType type, int x, int y, float angle, int speed, ASprite* sprite)
{
  float										scale = 0.f;

  AElement									*element;

  if ((element = ElementFactory::create(id, type)) == nullptr)
	return (element);
  if (sprite)
	element->setSprite(sprite);
  element->setCoords(new Coords(x, y));
  element->setAngle(angle);
  element->setSpeed(std::chrono::milliseconds(speed));
  if (element->getType() == RType::SET)
  {
	scale = (float)this->windowSize->y / 300;
	element->setScale(scale);
  }
  this->windowQueue->push(element);
  return (element);
}

void		GraphicalController::removeElement(AElement *element)
{
  this->windowQueue->remove(element);
}

Event *		GraphicalController::eventAction(void)
{
	return this->eventQueue->pop();
}

void		GraphicalController::scoreAction(int _score)
{
  if (!this->score_elem)
  {
	  std::cout << "coucou " << std::endl;
	this->score_elem = ElementFactory::create(0, RType::SCORE);
	this->score_elem->setCoords(new Coords(0, 410));
	this->score_elem->setAngle(0);
	this->score_elem->setSpeed(std::chrono::milliseconds(0));
	this->score_elem->loadSprites(SFML);
	this->windowQueue->push(this->score_elem);
  }
  std::ostringstream	ss;
  ss << _score;

  this->score = _score;
  ((Score*)this->score_elem)->setString(ss.str());
  return;
}

bool			GraphicalController::checkIp(std::string ip)
{
	size_t n = std::count(ip.begin(), ip.end(), '.');

	if ((n < 3 || n > 3) || ip.size() < 7)
	{
		std::cout << "IP  non VALIDE" << std::endl;
		return (false);
	}
	std::cout << "ip valide" << std::endl;
	return (true);
}