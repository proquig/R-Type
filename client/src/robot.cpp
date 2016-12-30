#include "robot.hh"
#include "SFMLSprite.hh"

void	Robot::loadSprites(GLib lib)
{
	return;
}

void	Robot::print(void * window)
{
	this->animation = "DEFAULT";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->setAnimated(false);
	this->sprite->print(window);
}