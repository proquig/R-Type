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
		this->skin = "ARC";
		break;
	}
}

void	Missile::loadSprites(GLib lib)
{
  /*
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet9.gif");
		break;
	}

	this->sprite->addRessource("DEFAULT", std::vector<Cut *>{
			/*new Cut(54, 540, 13, 60),
			new Cut(71, 540, 29, 60),
			new Cut(104, 540, 28, 60),
			new Cut(137, 540, 37, 60),
			new Cut(186, 540, 47, 60),
			new Cut(235, 540, 55, 60),
			new Cut(40, 606, 62, 60),
			new Cut(105, 606, 64, 60),
			new Cut(172, 606, 60, 60),
			new Cut(235, 606, 65, 60),
			new Cut(40, 672, 64, 60),
			new Cut(105, 672, 61, 60),
			new Cut(170, 672, 59, 60),
			new Cut(238, 672, 59, 60)*/
				/*new Cut(37, 738, 65, 60),
				new Cut(30, 455, 65, 48),
				new Cut(30, 455, 65, 48),
				new Cut(70, 72, 30, 28)
	});




	this->sprite->setAnimated(true);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(true);
*/
}

void	Missile::print(void * window)
{
	this->sprite->setAnimation(this->skin, this->coords, 1);
	this->sprite->print(window);
}
