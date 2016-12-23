#include "set.hh"
#include "SFMLSprite.hh"

Set::Set(Land land)
{
	switch (land) {
	case WASTE:
		this->land = "WASTE_LAND";
		this->size = new Coords(1000, 300);
		break;
	default :
		this->land = "WASTE_LAND";
		break;
	}
	this->tic = std::chrono::milliseconds::zero();
}

void	Set::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/WASTE_LAND.png");
		break;
	}

	this->sprite->addRessource("WASTE_LAND", std::vector<Cut *>{new Cut(0, 0, this->size->x, this->size->y)});
	this->sprite->setAnimated(false);
	this->sprite->setAnimTime(500);
	this->sprite->setLoop(false);
}

void							Set::print(void * window)
{
	std::chrono::milliseconds	now = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
	std::chrono::milliseconds	deltaTime = now - this->tic;

	if (deltaTime > this->speed) {
		this->tic = now;
		this->coords->x -= 2;
		if ((this->coords->x * -1) >= this->size->x) {
			std::cout << this->size->x << std::endl;
			this->coords->x = 0;
		}
	}
	this->sprite->setAnimation(this->land, this->coords, this->scale);
	this->sprite->print(window);
	this->sprite->setAnimation(this->land, new Coords(this->coords->x + this->size->x, 0), this->scale);
	this->sprite->print(window);
}