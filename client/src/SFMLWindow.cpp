#include "SFMLWindow.hh"
#include "IObservable.hpp"


////////////////////////////////////////////////////////////////////
// WINDOW
////////////////////////////////////////////////////////////////////

void	SFMLWindow::run(WorkQueue<AElement *> *_elemqueue, WorkQueue<Event *> *_eventqueue, IObservable* _obs)
{
	this->elementQueue = _elemqueue;
	this->eventQueue = _eventqueue;
	this->obs = _obs;
	this->scene = std::vector<AElement *>();
	if (!this->handler)
		this->handler = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->name);
	this->handler->clear(sf::Color::Black);
  	this->handler->setFramerateLimit(0);
  	//this->handler->setVerticalSyncEnabled(true);
	while (this->handler->isOpen())
	{
		this->pollEvent();
	  	this->renderScene();
	  	this->render();
		std::this_thread::sleep_for(std::chrono::milliseconds(2));
	}
	//delete this->handler;
}

void											SFMLWindow::renderScene(void)
{
	std::vector<AElement *>						*elements;
	std::vector<AElement *>::const_iterator		element;
	std::vector<AElement *>::const_iterator		elem;
	bool										match = false;
	Coords										*position;

  if (!this->elementQueue->getQueue().size())
	return;
  elements = this->elementQueue->popAll();

	for (element = this->scene.begin(); element != this->scene.end(); ) {
		if ((*element)->getTtl() <= (float)0.0 && (*element)->getType() != RType::SET && (*element)->getType() != RType::SCORE) {
            element = this->scene.erase(element);
		}
		else
			element++;
	}

	if (!elements->size())
		return;
	for (element = elements->begin(); element != elements->end(); ++element) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			if ((*elem)->getId() == (*element)->getId() && (*element)->getType() == (*elem)->getType()) {
				position = (*element)->getCoords();
				(*elem)->move(position->x, position->y, (*element)->getAngle(), (*element)->getSpeed());
				match = true;
			}
		}

		if (!match) {
			(*element)->loadSprites(SFML);
			this->scene.push_back(*element);
		}
		match = false;
	}
	delete elements;
}

void											SFMLWindow::render(void)
{
	std::vector<AElement *>::const_iterator		element;
	Coords										*coords;
	Coords										*target;
	Coords										*distance;

	if (!this->scene.size())
	  return;
	  //std::cout << "SIZESIZE=" << this->scene.size() << std::endl;
	  this->handler->clear();
		for (element = this->scene.begin(); element != this->scene.end(); ++element)
		{
			coords = (*element)->getCoords();
			target = (*element)->getTarget();
			distance = (*element)->getDistance();
			//coords->x = target->x;
			//coords->y = target->y;
		  	if (coords->x != target->x || coords->y != target->y || (*element)->getType())
			{
			  if (coords->x < target->x)
				coords->x += distance->x;
			  else if (coords->x > target->x)
				coords->x += distance->x;
			if (coords->y < target->y)
				coords->y += distance->y;
			else if (coords->y > target->y)
				coords->y += distance->y;
			(*element)->print((void *)this->handler);
			}
		}
	this->handler->display();
}

////////////////////////////////////////////////////////////////////
// EVENT
////////////////////////////////////////////////////////////////////

void	SFMLWindow::pollEvent(void)
{
	while (this->handler->pollEvent(this->event))
	{
		sf::Vector2i mouse = sf::Mouse::getPosition();
		sf::Vector2u size = this->handler->getSize();
		unsigned int _x = mouse.x;
		unsigned int _y = mouse.y;
		unsigned int _w = size.x;
		unsigned int _h = size.y;

		switch (event.type)
		{
			case sf::Event::Closed:
				this->eventQueue->push(new Event(Event::QUIT, RType::NONE, "QUIT", _x, _y, _w, _h));
				this->handler->close();
				break;
			case sf::Event::Resized:
				this->eventQueue->push(new Event(Event::RESIZE, RType::NONE, "RESIZE", _x, _y, _w, _h));
				break;
			case sf::Event::KeyPressed:
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::UP, "UP", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Down:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::DOWN, "DOWN", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Left:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::LEFT, "LEFT", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Right:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::RIGHT, "RIGHT", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Space:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::SPACE, "SPACE", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Return:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "ENTER", _x, _y, _w, _h));
						break;
					default:
						break;
				}
				break;
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
					case sf::Keyboard::Up:
						this->eventQueue->push(new Event(Event::KEYRELEASE, RType::UP, "UP", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Down:
						this->eventQueue->push(new Event(Event::KEYRELEASE, RType::DOWN, "DOWN", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Left:
						this->eventQueue->push(new Event(Event::KEYRELEASE, RType::LEFT, "LEFT", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Right:
						this->eventQueue->push(new Event(Event::KEYRELEASE, RType::RIGHT, "RIGHT", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Space:
						this->eventQueue->push(new Event(Event::KEYRELEASE, RType::SPACE, "SPACE", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Return:
						this->eventQueue->push(new Event(Event::KEYRELEASE, RType::ENTER, "ENTER", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num0:
					case sf::Keyboard::Numpad0:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "0", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num1:
					case sf::Keyboard::Numpad1:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "1", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num2:
					case sf::Keyboard::Numpad2:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "2", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num3:
					case sf::Keyboard::Numpad3:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "3", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num4:
					case sf::Keyboard::Numpad4:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "4", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num5:
					case sf::Keyboard::Numpad5:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "5", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num6:
					case sf::Keyboard::Numpad6:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "6", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num7:
					case sf::Keyboard::Numpad7:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "7", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num8:
					case sf::Keyboard::Numpad8:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "8", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Num9:
					case sf::Keyboard::Numpad9:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "9", _x, _y, _w, _h));
						break;
					case sf::Keyboard::Period:
					case sf::Keyboard::SemiColon:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, ".", _x, _y, _w, _h));
						break;
					case sf::Keyboard::BackSpace:
						this->eventQueue->push(new Event(Event::KEYPRESS, RType::ENTER, "SUPPR", _x, _y, _w, _h));
						break;
					default:
						break;
				}
				break;
			default:
				break;
		}
		if (obs && !this->eventQueue->empty())
			obs->notify(0);
	}
}

void *	SFMLWindow::getHandler(void)
{
	return (void *)this->handler;
}

int		SFMLWindow::getWidth(void)
{
	return this->width;
}

int		SFMLWindow::getHeight(void)
{
	return this->height;
}

void SFMLWindow::setProperty(IWindow::eProperty property, bool flag)
{
  /*
  switch (property)
  {
    case KEY_REPEAT:
      handler->setKeyRepeatEnabled(flag);
      break;
    default:
      break;
  }
   */
}
