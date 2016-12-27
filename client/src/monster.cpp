#include "monster.hh"
#include "SFMLSprite.hh"

void	Monster::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet5.gif");
		break;
	}

	this->sprite->addRessource("DEFAULT", std::vector<Cut *>{
		new Cut(0, 0, 32, 30),
			new Cut(32, 0, 32, 30),
			new Cut(64, 0, 32, 30),
			new Cut(96, 0, 32, 30),
			new Cut(128, 0, 32, 30),
			new Cut(160, 0, 32, 30),
			new Cut(192, 0, 32, 30),
			new Cut(224, 0, 32, 30),
	});
	
	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);
}

void	Monster::print(void * window)
{
	this->animation = "CYAN_STAY";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->print(window);
}
