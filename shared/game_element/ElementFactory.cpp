#include "ElementFactory.hh"

ElementFactory::ElementFactory()
{
	_elementId = 0;
}

ElementFactory::~ElementFactory()
{}

AElement*		ElementFactory::create(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	switch (type)
	{
		case AElement::PLAYER :
			return createPlayer(x, y, hp, sizex, sizey, damage, angle, speed);
		case AElement::BULLET :
			return createShot(idFrom, x, y, sizex, sizey, damage, angle, speed);
		case AElement::DECOR :
			return createDecor(x, y, sizex, sizey);
		case AElement::MONSTER :
			return createMonster(x, y, hp, sizex, sizey, damage, angle, speed);

	}
}

Player*			ElementFactory::createPlayer(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Player*		player = new Player(-1, _elementId++, AElement::PLAYER, x, y, hp, sizex, sizey, damage, angle, speed);
	return player;
}

Shot*			ElementFactory::createShot(uint32_t idFrom, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Shot*		shot = new Shot(idFrom, _elementId++, AElement::BULLET, x, y, 1, sizex, sizey, damage, angle, speed);
	return shot;
}

Decor*			ElementFactory::createDecor(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey)
{
	Decor*		decor = new Decor(-1, _elementId++, AElement::DECOR, x, y, 100000, sizex, sizey, 0, 0, 0);
	return decor;
}

Monster*		ElementFactory::createMonster(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Monster*		monster = new Monster(-1, _elementId++, AElement::MONSTER, x, y, hp, sizex, sizey, damage, angle, speed);
	return monster;
}