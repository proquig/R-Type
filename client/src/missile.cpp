#include "missile.hh"
#include "SFMLSprite.hh"

Missile::Missile(Type _type)
{
	switch (_type)
	{
	case DEFAULT:
		this->skin = "DEFAULT";
		break;
	default:
		this->skin = "DEFAULT";
		break;
	}
}

void	Missile::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet2.gif");
		break;
	}

	this->sprite->addRessource("DEFAULT", std::vector<Cut *>{
		new Cut(300, 300, 200, 200)
	});

	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);
}

void	Missile::print(void * window)
{
	this->sprite->setAnimation(this->skin, this->coords, 1);
	this->sprite->print(window);
}
