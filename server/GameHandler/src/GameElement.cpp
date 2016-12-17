#include "GameElement.hh"

GameElement::GameElement()
{
}

GameElement::~GameElement()
{
}

uint32_t				GameElement::getIdFrom() const
{
	return _idFrom;
}

uint32_t				GameElement::getId() const
{
	return _id;
}

uint16_t				GameElement::getType() const
{
	return _type;
}

uint16_t				GameElement::getX() const
{
	return _x;
}

uint16_t				GameElement::getY() const
{
	return _y;
}

float 					GameElement::getAngle() const
{
	return _angle;
}

char					GameElement::getSpeed() const
{
	return _speed;
}

void					GameElement::setIdFrom(uint32_t idFrom)
{
	_idFrom = idFrom;
}

void					GameElement::setId(uint32_t id)
{
	_id = id;
}

void					GameElement::setType(uint16_t type)
{
	_type = type;
}

void					GameElement::setX(uint16_t x)
{
	_x = x;
}

void					GameElement::setY(uint16_t y)
{
	_y = y;
}

void					GameElement::setSizeX(uint16_t x)
{
	_size_x = x;
}

void					GameElement::setSizeY(uint16_t y)
{
	_size_y = y;
}

void					GameElement::setAngle(float angle)
{
	_angle = angle;
}

void					GameElement::setSpeed(char speed)
{
	_speed = speed;
}