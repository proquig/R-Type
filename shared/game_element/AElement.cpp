#include "AElement.hh"

AElement::AElement()
{
}

AElement::~AElement()
{
}

uint32_t				AElement::getIdFrom() const
{
	return _idFrom;
}

uint32_t				AElement::getId() const
{
	return _id;
}

uint16_t				AElement::getType() const
{
	return _type;
}

uint16_t				AElement::getX() const
{
	return _x;
}

uint16_t				AElement::getY() const
{
	return _y;
}

uint16_t				AElement::getHp() const
{
	return _hp;
}

float 					AElement::getAngle() const
{
	return _angle;
}

char					AElement::getSpeed() const
{
	return _speed;
}

void					AElement::setIdFrom(uint32_t idFrom)
{
	_idFrom = idFrom;
}

void					AElement::setId(uint32_t id)
{
	_id = id;
}

void					AElement::setType(uint16_t type)
{
	_type = type;
}

void					AElement::setX(uint16_t x)
{
	_x = x;
}

void					AElement::setY(uint16_t y)
{
	_y = y;
}


uint16_t AElement::getSizeX() const
{
	return _size_x;
}

uint16_t AElement::getSizeY() const
{
	return _size_y;
}

void					AElement::setSizeX(uint16_t x)
{
	_size_x = x;
}

void					AElement::setSizeY(uint16_t y)
{
	_size_y = y;
}

void					AElement::setHp(uint16_t hp)
{
	_hp = hp;
}

void					AElement::setAngle(float angle)
{
	_angle = angle;
}

void					AElement::setSpeed(char speed)
{
	_speed = speed;
}

std::vector<IElement*>					AElement::collideWith(IElement* elem)
{
	std::cout << this->getId() << " collides with " << elem->getId() << std::endl;
	return std::vector<IElement*>();
}
