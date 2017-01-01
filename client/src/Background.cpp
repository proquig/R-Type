#include "Background.hh"
#include "SFMLSprite.hh"

Background::Background(Image _image)
{
	switch (_image) {
	case GAME_OVER:
		this->image = "GAME_OVER";
		this->size = new Coords(800, 450);
		break;
	default :
		break;
	}
}

void	Background::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/game_over.png");
		break;
	}

	this->sprite->addRessource("GAME_OVER", std::vector<Cut *>{new Cut(0, 0, this->size->x, this->size->y)});
	this->sprite->setAnimated(false);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(false);
}

void							Background::print(void * window)
{
	this->coords->x = 0;
	this->coords->y = 0;
	this->sprite->setAnimation(this->image, this->coords, 1);
	this->sprite->print(window);
}