#include "SFMLWindow.hh"

void	SFMLWindow::init(void)
{
	std::cout << "SFMLWindow init()" << std::endl;

	this->window = new sf::RenderWindow(sf::VideoMode(this->width, this->height), this->name);

	while (this->window->isOpen())
	{
		sf::Event event;
		while (this->window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				this->window->close();
		}
		this->window->clear(sf::Color::Black);
		this->window->display();
	}
}

int		SFMLWindow::getWidth(void)
{
	return this->width;
}

int		SFMLWindow::getHeight(void)
{
	return this->height;
}