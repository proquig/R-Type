#include "monster.hh"
#include "SFMLSprite.hh"

void	Monster::loadSprites(GLib lib)
{
  /*
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet23.gif");
		break;
	}

	this->sprite->addRessource("DEFAULT", std::vector<Cut *>{
		new Cut(0, 0, 33, 35),
			new Cut(33, 0, 33, 35),
			new Cut(66, 0, 33, 35),
			new Cut(99, 0, 33, 35),
			new Cut(132, 0, 33, 35),
			new Cut(165, 0, 33, 35),
			new Cut(196, 0, 33, 35),
			new Cut(229, 0, 33, 35)
	});
	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);
   */
}

void	Monster::print(void * window)
{
	this->animation = "DEFAULT";
	this->size->x = 50;
	this->size->y = 50;
	this->sprite->setAnimation(this->animation, this->coords, 1);
  	this->sprite->setAnimated(false);
	this->sprite->print(window);
}
