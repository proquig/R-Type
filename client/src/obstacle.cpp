#include "obstacle.hh"
#include "SFMLSprite.hh"

void	Obstacle::loadSprites(GLib lib)
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

void	Obstacle::print(void * window)
{
	this->animation = "CYAN_STAY";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, this->size);
	this->sprite->print(window);
}

void	Obstacle::move(int _x, int _y, float _angle, int _speed)
{
	this->coords->x = _x;
	this->coords->y = _y;
	this->angle = _angle;
	this->speed = _speed;
}

void	Obstacle::destroy()
{

}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Obstacle::setId(unsigned int _id)
{
	this->id = _id;
}

void	Obstacle::setAnimation(std::string _animation)
{
	this->animation = _animation;
}

void	Obstacle::setSize(Coords *_size)
{
	this->size = _size;
}
