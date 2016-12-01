#include "SFMLWindow.hh"

void	SFMLWindow::run(WorkQueue<AElement *> *_elemqueue, WorkQueue<Event *> *_eventqueue)
{
	this->elementQueue = _elemqueue;
	this->eventQueue = _eventqueue;
	this->handler = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->name);

	while (this->handler->isOpen())
	{
		this->pollEvent();
		this->render();
	}
}

void	SFMLWindow::render(void)
{
	this->handler->clear(sf::Color::Black);
	this->handler->display();
}

void	SFMLWindow::pollEvent(void)
{
	while (this->handler->pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->eventQueue->push(new Event(Event::QUIT, 0, 0));
			this->handler->close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Up:
				this->eventQueue->push(new Event(Event::UP, 0, 0));
				break;
			case sf::Keyboard::Down:
				this->eventQueue->push(new Event(Event::DOWN, 0, 0));
				break;
			case sf::Keyboard::Left:
				this->eventQueue->push(new Event(Event::LEFT, 0, 0));
				break;
			case sf::Keyboard::Right:
				this->eventQueue->push(new Event(Event::RIGHT, 0, 0));
				break;
			case sf::Keyboard::Return:
				this->eventQueue->push(new Event(Event::ENTER, 0, 0));
				break;
			default:
				break;
			}
			break;
		default:
			break;
		}
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