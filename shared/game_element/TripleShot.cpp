#include "TripleShot.hh"

TripleShot::TripleShot(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed) : Shot::Shot(idFrom, id, type, x, y, hp, sizex, sizey, damage, angle, speed)
{
	_startX = x;
}

TripleShot::~TripleShot()
{
}

bool									TripleShot::move()
{
	this->setX(this->getX() + (this->getSpeed() * (this->getAngle() == (float)90 ? 1 : -1)));
	if (_activated)
		_activated = false;
	if (abs(_x - _startX) > 100 && !_activated)
		_activated = true;
	return true;
}

std::vector<RType::IElement*>			TripleShot::collideWith(RType::IElement* elem)
{
	return std::vector<RType::IElement*>();
}

bool									TripleShot::isActivated() const
{
	return _activated;
}