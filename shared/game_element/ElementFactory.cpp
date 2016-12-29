#include "ElementFactory.hh"

ElementFactory::ElementFactory()
{
	_elementId = 5;
}

ElementFactory::~ElementFactory()
{}

RType::AElement*		ElementFactory::create(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	switch (type)
	{
		case RType::PLAYER :
			return createPlayer(x, y, hp, sizex, sizey, damage, angle, speed);
		case RType::BULLET :
			return createShot(idFrom, x, y, sizex, sizey, damage, angle, speed);
		case RType::DECOR :
			return createDecor(x, y, sizex, sizey);
		case RType::MONSTER :
			return createMonster(x, y, hp, sizex, sizey, damage, angle, speed);
		default:
			break;
	}
	return nullptr;
}

Player*			ElementFactory::createPlayer(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Player*		player = new Player(-1, this->newID(), x, y, hp, sizex, sizey, damage, angle, speed);
	return player;
}

Shot*			ElementFactory::createShot(uint32_t idFrom, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Shot*		shot = new Shot(idFrom, this->newID(), RType::BULLET, x, y, 1, sizex, sizey, damage, angle, speed);
	return shot;
}

Decor*			ElementFactory::createDecor(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey)
{
	Decor*		decor = new Decor(-1, this->newID(), RType::DECOR, x, y, 100000, sizex, sizey, 0, 0, 0);
	return decor;
}

RType::AElement*		ElementFactory::createMonster(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Monster*		monster = new Monster(-1, RType::MONSTER, x, y, hp, sizex, sizey, damage, angle, speed, this);
	return monster;
}

unsigned int ElementFactory::newID()
{
  if (this->_elementId == ((unsigned int)-1))
	this->_elementId = 5;
  this->_elementId++;
  return (this->_elementId - 1);
}
