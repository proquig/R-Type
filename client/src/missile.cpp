#include "missile.hh"
#include "SFMLSprite.hh"

void	Missile::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet42.gif");
		break;
	}

	this->sprite->addRessource("CYAN_STAY", std::vector<Cut *>{new Cut(66, 0, 33, 19), new Cut(33, 0, 33, 19), new Cut(0, 0, 33, 19)});

	// Init on cyan_stay
	this->sprite->setAnimation("CYAN_STAY", new Coords(0, 0), new Coords(50, 50));

	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);
}

void	Missile::print(void * window)
{
	this->sprite->setAnimation(this->animation, this->coords, this->size);
	this->sprite->print(window);
}

void	Missile::move(int x, int y)
{
	this->coords->x = x;
	this->coords->y = y;
}

void	Missile::destroy()
{

}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Missile::setId(unsigned int _id)
{
	this->id = _id;
}

void	Missile::setAnimation(std::string _animation)
{
	this->animation = _animation;
}

void	Missile::setSize(Coords *_size)
{
	this->size = _size;
}

/////////////////////////////////////////////////////////////////
// GETTERS
/////////////////////////////////////////////////////////////////

unsigned int	Missile::getId(void) const
{
	return (this->id);
}

Coords *		Missile::getCoords(void) const
{
	return (this->coords);
}

Coords *	Missile::getSize(void) const
{
	return (this->size);
}

std::string		Missile::getAnimation(void) const
{
	return (this->animation);
}