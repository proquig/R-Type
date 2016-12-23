#include "obstacle.hh"
#include "SFMLSprite.hh"

Obstacle::Obstacle(Skin _skin)
{
	switch (_skin) {
	default:
		this->skin = "DEFAULT";
		break;
	}
}

void	Obstacle::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet17.gif");
		break;
	}

	this->sprite->addRessource("DEFAULT", std::vector<Cut *>{
		new Cut(0, 0, 65, 140),
		new Cut(65, 0, 65, 140),
		new Cut(130, 0, 65, 140),
		new Cut(195, 0, 65, 140),
		new Cut(260, 0, 65, 140),
		new Cut(326, 0, 65, 140),
		new Cut(390, 0, 65, 140),
		new Cut(455, 0, 65, 140)
	});

	this->sprite->setAnimTime(100);

}

void	Obstacle::print(void * window)
{
	this->animation = this->skin;
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimated(true);
	this->sprite->setLoop(true);
	this->sprite->setAnimation(this->animation, this->coords, 1);
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