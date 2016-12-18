#include "SFMLWindow.hh"

////////////////////////////////////////////////////////////////////
// WINDOW
////////////////////////////////////////////////////////////////////

void	SFMLWindow::run(WorkQueue<AElement *> *_elemqueue, WorkQueue<Event *> *_eventqueue)
{
	this->elementQueue = _elemqueue;
	this->eventQueue = _eventqueue;
	this->scene = std::vector<AElement *>();
	this->handler = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->name);
	this->handler->clear(sf::Color::Black);
	while (this->handler->isOpen())
	{
		this->pollEvent();
		this->renderScene();
		this->render();
	}
}


void											SFMLWindow::renderScene(void)
{
	std::vector<AElement *>						*elements;
	std::vector<AElement *>::const_iterator		element;
	std::vector<AElement *>::const_iterator		elem;
	bool										match = false;

	elements = this->elementQueue->popAll();
	if (!elements->size())
		return;
	for (element = elements->begin(); element != elements->end(); ++element) {
		for (elem = this->scene.begin(); elem != this->scene.end(); ++elem) {
			if ((*elem)->getId() == (*element)->getId()) {
				(*elem)->move((*element)->getCoords());
				(*elem)->setSize((*element)->getSize());
				(*elem)->setAnimation((*element)->getAnimation());
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

	if (!this->scene.size())
		return;
	for (element = this->scene.begin(); element != this->scene.end(); ++element)
		(*element)->print((void *)this->handler);
	this->handler->display();
}

////////////////////////////////////////////////////////////////////
// EVENT
////////////////////////////////////////////////////////////////////

void	SFMLWindow::pollEvent(void)
{
	while (this->handler->pollEvent(this->event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			this->eventQueue->push(new Event(Event::QUIT, "QUIT", 0, 0));
			this->handler->close();
			break;
		case sf::Event::KeyPressed:
			switch (event.key.code) {
			case sf::Keyboard::Up:
				this->eventQueue->push(new Event(Event::UP, "UP", 0, 0));
				break;
			case sf::Keyboard::Down:
				this->eventQueue->push(new Event(Event::DOWN, "DOWN", 0, 0));
				break;
			case sf::Keyboard::Left:
				this->eventQueue->push(new Event(Event::LEFT, "LEFT", 0, 0));
				break;
			case sf::Keyboard::Right:
				this->eventQueue->push(new Event(Event::RIGHT, "RIGHT", 0, 0));
				break;
			case sf::Keyboard::Return:
				this->eventQueue->push(new Event(Event::ENTER, "ENTER", 0, 0));
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