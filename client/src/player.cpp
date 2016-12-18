#include "player.hh"
#include "SFMLSprite.hh"

void	Player::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite(".\\..\\..\\client\\media\\GAME-Assets\\r-typesheet42.gif");
		break;
	}

	this->sprite->addRessource("cyan_stay", std::vector<Cut *>{new Cut(66, 0, 33, 19), new Cut(33, 0, 33, 19), new Cut(0, 0, 33, 19)});
	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);

	// Init on cyan_stay
	this->sprite->setAnimation("cyan_stay", new Coords(0, 0), new Coords(50, 50));
}

void	Player::print(void * window)
{
	this->sprite->setAnimation(this->animation, this->coords, this->size);
	this->sprite->print(window);
}

void	Player::move(Coords *to)
{
	this->coords = to;
}

void	Player::destroy()
{

}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Player::setId(unsigned int _id)
{
	this->id = _id;
}

void	Player::setAnimation(std::string _animation)
{
	this->animation = _animation;
}

void	Player::setSize(Coords *_size)
{
	this->size = _size;
}

/////////////////////////////////////////////////////////////////
// GETTERS
/////////////////////////////////////////////////////////////////

unsigned int	Player::getId(void) const
{
	return (this->id);
}

Coords *		Player::getCoords(void) const
{
	return (this->coords);
}

Coords *	Player::getSize(void) const
{
	return (this->size);
}

std::string		Player::getAnimation(void) const
{
	return (this->animation);
}