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

	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);
}

void	Missile::print(void * window)
{
	this->animation = "CYAN_STAY";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->print(window);
}

void	Missile::move(int _x, int _y, float _angle, int _speed)
{
	this->coords->x = _x;
	this->coords->y = _y;
	this->angle = _angle;
	this->speed = _speed;
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
