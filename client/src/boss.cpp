#include "boss.hh"
#include "SFMLSprite.hh"

void	Boss::loadSprites(GLib lib)
{
	return;
}

void	Boss::print(void * window)
{
	this->animation = "DEFAULT";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->setAnimated(false);
	this->sprite->print(window);
}