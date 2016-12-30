#include "player.hh"

Player::Player(Color color)
{
	switch (color) {
	case CYAN:
		this->skin = "CYAN";
		break;
	case VIOLET:
		this->skin = "VIOLET";
		break;
	case GREEN:
		this->skin = "GREEN";
		break;
	case RED:
		this->skin = "RED";
		break;
	case BLUE:
		this->skin = "BLUE";
		break;
	}
}

void	Player::loadSprites(GLib lib)
{
}

void	Player::print(void * window)
{
	this->animation = this->skin;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->setAnimated(false);
	this->sprite->print(window);
}
