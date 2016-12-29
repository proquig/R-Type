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
  /*
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet42.gif");
		break;
	}

	this->size->x = 50;
	this->size->y = 50;

	this->sprite->addRessource("CYAN_DOWN", std::vector<Cut *>{new Cut(0, 0, 33, 19), new Cut(33, 0, 33, 19)});
	this->sprite->addRessource("CYAN", std::vector<Cut *>{new Cut(66, 0, 33, 19)});
	this->sprite->addRessource("CYAN_UP", std::vector<Cut *>{new Cut(99, 0, 33, 19), new Cut(132, 0, 33, 19)});

	this->sprite->addRessource("VIOLET_DOWN", std::vector<Cut *>{new Cut(0, 17, 33, 19), new Cut(33, 17, 33, 19)});
	this->sprite->addRessource("VIOLET", std::vector<Cut *>{new Cut(66, 17, 33, 19)});
	this->sprite->addRessource("VIOLET_UP", std::vector<Cut *>{new Cut(99, 17, 33, 19), new Cut(132, 17, 33, 19)});

	this->sprite->addRessource("GREEN_DOWN", std::vector<Cut *>{new Cut(0, 34, 33, 19), new Cut(33, 34, 33, 19)});
	this->sprite->addRessource("GREEN", std::vector<Cut *>{new Cut(66, 34, 33, 19)});
	this->sprite->addRessource("GREEN_UP", std::vector<Cut *>{new Cut(99, 34, 33, 19), new Cut(132, 34, 33, 19)});

	this->sprite->addRessource("RED_DOWN", std::vector<Cut *>{new Cut(0, 51, 33, 19), new Cut(33, 51, 33, 19)});
	this->sprite->addRessource("RED", std::vector<Cut *>{new Cut(66, 51, 33, 19)});
	this->sprite->addRessource("RED_UP", std::vector<Cut *>{new Cut(99, 51, 33, 19), new Cut(132, 51, 33, 19)});

	this->sprite->addRessource("BLUE_DOWN", std::vector<Cut *>{new Cut(0, 68, 33, 19), new Cut(33, 68, 33, 19)});
	this->sprite->addRessource("BLUE", std::vector<Cut *>{new Cut(66, 68, 33, 19)});
	this->sprite->addRessource("BLUE_UP", std::vector<Cut *>{new Cut(99, 68, 33, 19), new Cut(132, 68, 33, 19)});
	this->sprite->setAnimated(false);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(false);
   */
}

void	Player::print(void * window)
{
	/*
	if (this->coords->x < this->target->x)
		this->coords->x += 8;
	else if (this->coords->x > this->target->x)
		this->coords->x -= 8;
	if (this->coords->y < this->target->y)
		this->coords->y += 8;
	else if (this->coords->y > this->target->y)
		this->coords->y -= 8;
		*/
	this->animation = this->skin;
	this->sprite->setAnimation(this->animation, this->coords, 1);
	this->sprite->setAnimated(false);
	if (this->angle <= -45) {
		this->sprite->setAnimation(this->animation + "_UP", this->coords, 1);
		this->sprite->setAnimated(true);
	}
	if (this->angle >= 45) {
		this->sprite->setAnimation(this->animation + "_DOWN", this->coords, 1);
		this->sprite->setAnimated(true);
	}
	this->sprite->print(window);
}
