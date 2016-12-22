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
	this->handler = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->name);
	this->handler->clear(sf::Color::Black);
	while (this->handler->isOpen())
	{
		this->pollEvent();
		this->renderScene();
		this->render();
		std::this_thread::sleep_for(std::chrono::milliseconds(10));
	}
}


void											SFMLWindow::renderScene(void)
{
	std::vector<AElement *>						*elements;
	std::vector<AElement *>::const_iterator		element;
	std::vector<AElement *>::const_iterator		elem;
	bool										match = false;
	Coords										*position;

	elements = this->elementQueue->popAll();
	if (!elements->size())
		return;
	for (element = elements->begin(); element != elements->end(); ++element) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			if ((*elem)->getId() == (*element)->getId()) {
				position = (*element)->getCoords();
				(*elem)->move(position->x, position->y, (*element)->getAngle(), (*element)->getSpeed());
				match = true;
			}
		}
		if (!match) {
			(*element)->loadSprites(SFML);
			this->scene.push_back(*element);
		}
	}
}

void											SFMLWindow::render(void)
{
	std::vector<AElement *>::const_iterator		element;

	this->handler->clear();
	if (this->scene.size()) {
		for (element = this->scene.begin(); element != this->scene.end(); ++element)
			(*element)->print((void *)this->handler);
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
		sf::Vector2i	mouse = sf::Mouse::getPosition();
		sf::Vector2u	size = this->handler->getSize();
		unsigned int	_x = mouse.x;
		unsigned int	_y = mouse.y;
		unsigned int	_w = size.x;
		unsigned int	_h = size.y;
		
		switch (event.type)
		{
		case sf::Event::Closed:
			this->eventQueue->push(new Event(Event::QUIT, "QUIT", _x, _y, _w, _h));
			this->handler->close();
			break;
		case sf::Event::Resized:
			this->eventQueue->push(new Event(Event::RESIZE, "RESIZE", _x, _y, _w, _h));
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Up:
				this->eventQueue->push(new Event(Event::UP, "UP", _x, _y, _w, _h));
				break;
			case sf::Keyboard::Down:
				this->eventQueue->push(new Event(Event::DOWN, "DOWN", _x, _y, _w, _h));
				break;
			case sf::Keyboard::Left:
				this->eventQueue->push(new Event(Event::LEFT, "LEFT", _x, _y, _w, _h));
				break;
			case sf::Keyboard::Right:
				this->eventQueue->push(new Event(Event::RIGHT, "RIGHT", _x, _y, _w, _h));
				break;
			case sf::Keyboard::Return:
				this->eventQueue->push(new Event(Event::ENTER, "ENTER", _x, _y, _w, _h));
				break;
			default:
				return;
			}
			break;
		default:
			return;
		}
		if (obs)
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