#include "ElementFactory.hh"

ElementFactory::ElementFactory()
{
	_elementId = 0;
}

ElementFactory::~ElementFactory()
{}

Player*			ElementFactory::createPlayer(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Player*		player = new Player();
	player->setIdFrom(-1);
	player->setId(_elementId++);
	player->setType(AElement::PLAYER);
	player->setX(x);
	player->setY(y);
	player->setHp(hp);
	player->setSizeX(sizex);
	player->setSizeY(sizey);
	player->setAngle(0);
	player->setSpeed(speed);
	player->setDamage(damage);
	return player;
}

Shot*			ElementFactory::createShot(uint32_t idFrom, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	Shot*		shot = new Shot();
	shot->setIdFrom(idFrom);
	shot->setId(_elementId++);
	shot->setType(AElement::BULLET);
	shot->setX(x);
	shot->setY(y);
	shot->setHp(1);
	shot->setSizeX(sizex);
	shot->setSizeY(sizey);
	shot->setAngle(angle);
	shot->setSpeed(speed);
	shot->setDamage(damage);
	return shot;
}

Decor*			ElementFactory::createDecor(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey)
{
	Decor*		decor = new Decor();
	decor->setIdFrom(-1);
	decor->setId(_elementId++);
	decor->setType(AElement::DECOR);
	decor->setX(x);
	decor->setY(y);
	decor->setHp(1000000);
	decor->setSizeX(sizex);
	decor->setSizeY(sizey);
	decor->setAngle(0);
	decor->setSpeed(0);
	decor->setDamage(0);
	return decor;

}