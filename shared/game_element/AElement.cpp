#include "AElement.hh"

RType::AElement::AElement()
{
}

RType::AElement::AElement(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
{
	_idFrom = idFrom;
	_id = id;
	_type = type;
	_x = x;
	_y = y;
	_hp = hp;
	_size_x = sizex;
	_size_y = sizey;
	_speed = speed;
	_angle = angle;
	_damage = damage;
}

RType::AElement::~AElement()
{
}

uint32_t				RType::AElement::getIdFrom() const
{
	return _idFrom;
}

uint32_t				RType::AElement::getId() const
{
	return _id;
}

uint16_t				RType::AElement::getType() const
{
	return _type;
}

uint16_t				RType::AElement::getX() const
{
	return _x;
}

uint16_t				RType::AElement::getY() const
{
	return _y;
}

uint16_t				RType::AElement::getHp() const
{
	return _hp;
}

float 					RType::AElement::getAngle() const
{
	return _angle;
}

char					RType::AElement::getSpeed() const
{
	return _speed;
}

void					RType::AElement::setIdFrom(uint32_t idFrom)
{
	_idFrom = idFrom;
}

void					RType::AElement::setId(uint32_t id)
{
	_id = id;
}

void					RType::AElement::setType(uint16_t type)
{
	_type = type;
}

void					RType::AElement::setX(uint16_t x)
{
	_x = x;
}

void					RType::AElement::setY(uint16_t y)
{
	_y = y;
}


uint16_t RType::AElement::getSizeX() const
{
	return _size_x;
}

uint16_t RType::AElement::getSizeY() const
{
	return _size_y;
}

void					RType::AElement::setSizeX(uint16_t x)
{
	_size_x = x;
}

void					RType::AElement::setSizeY(uint16_t y)
{
	_size_y = y;
}

void					RType::AElement::setHp(uint16_t hp)
{
	_hp = hp;
}

void					RType::AElement::setAngle(float angle)
{
	_angle = angle;
}

void					RType::AElement::setSpeed(char speed)
{
	_speed = speed;
}

void					RType::AElement::setDamage(uint16_t damage)
{
	_damage = damage;
}

uint16_t				RType::AElement::getDamage() const
{
	return _damage;
}

std::vector<RType::IElement*>					RType::AElement::collideWith(RType::IElement* elem)
{
	return std::vector<RType::IElement*>();
}
