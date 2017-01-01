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
  int count = 0;
  this->windowQueue->lock();
  if (this->oldWindowQueue)
  {
	std::cout << "OLDQ SIZE = " << this->oldWindowQueue->size() << std::endl;
	for (AElement *element : *this->oldWindowQueue)
	  if (element->getId())
	  {
		count++;
		delete element;
	  }
	std::cout << "DELETED OLDQ SIZE = " << count << std::endl;
	this->oldWindowQueue->clear();
  }
  this->windowQueue->unlock();
  this->oldWindowQueue = this->windowQueue->popAll();
  //this->windowQueue->lock();
  count = 0;
  std::cout << "NEWQ SIZE = " << this->oldWindowQueue->size() << std::endl;
  for (AElement* element : *this->oldWindowQueue)
	if (element->getId())
	{
	  this->windowQueue->remove(element);
	  count++;
	}
  std::cout << "CREATED NEWQ SIZE = " << count << std::endl;
  //this->windowQueue->unlock();
}

AElement*	GraphicalController::elementAction(unsigned int id, RType::eType type, int x, int y, float angle, int speed, ASprite* sprite)
{
  float										scale = 0.f;

  AElement									*element;

  element = ElementFactory::create(id, type);
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
	this->score_elem = ElementFactory::create(0, RType::SCORE);
	this->score_elem->setCoords(new Coords(0, 410));
	this->score_elem->setAngle(0);
	this->score_elem->setSpeed(std::chrono::milliseconds(0));
	this->score_elem->loadSprites(SFML);
  }
  if (_score == this->score)
	return;
  std::ostringstream	ss;
  ss << _score;

  this->score = _score;
  ((Score*)this->score_elem)->setString(ss.str());
  this->windowQueue->push(this->score_elem);
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