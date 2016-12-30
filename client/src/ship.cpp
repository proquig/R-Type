#include "ship.hh"
#include "SFMLSprite.hh"

void	Ship::loadSprites(GLib lib)
{
	return;
}

void	Ship::print(void * window)
{
	this->animation = "DEFAULT";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->setAnimated(false);
	this->sprite->print(window);
}