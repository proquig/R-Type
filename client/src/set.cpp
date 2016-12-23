#include "set.hh"
#include "SFMLSprite.hh"

Set::Set(Land land)
{
	switch (land) {
	case WASTE:
		this->land = "WASTE_LAND";
		break;
	default :
		this->land = "WASTE_LAND";
		break;
	}
}

void	Set::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/WASTE_LAND.png");
		break;
	}

	this->sprite->addRessource("WASTE_LAND", std::vector<Cut *>{new Cut(0, 0, 1000, 300)});
	this->sprite->setAnimated(false);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(false);
}

void	Set::print(void * window)
{
	this->sprite->setAnimation(this->land, this->coords, this->scale);
	this->sprite->print(window);
}

void	Set::move(int _x, int _y, float _angle, int _speed)
{
	this->coords->x = _x;
	this->coords->y = _y;
	this->angle = _angle;
	this->speed = _speed;
}

void	Set::destroy()
{

}
