#include "set.hh"
#include "SFMLSprite.hh"

void	Set::loadSprites(GLib lib)
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

void	Set::print(void * window)
{
	this->sprite->setAnimation(this->animation, this->coords, this->size);
	this->sprite->print(window);
}

void	Set::move(int x, int y)
{
	this->coords->x = x;
	this->coords->y = y;
}

void	Set::destroy()
{

}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Set::setId(unsigned int _id)
{
	this->id = _id;
}

void	Set::setAnimation(std::string _animation)
{
	this->animation = _animation;
}

void	Set::setSize(Coords *_size)
{
	this->size = _size;
}

/////////////////////////////////////////////////////////////////
// GETTERS
/////////////////////////////////////////////////////////////////

unsigned int	Set::getId(void) const
{
	return (this->id);
}

Coords *		Set::getCoords(void) const
{
	return (this->coords);
}

Coords *	Set::getSize(void) const
{
	return (this->size);
}

std::string		Set::getAnimation(void) const
{
	return (this->animation);
}