#include "Shot.hh"

Shot::Shot(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed) : GameElement::GameElement(idFrom, id, type, x, y, hp, sizex, sizey, damage, angle, speed)
{
}

Shot::~Shot()
{
}

bool									Shot::move()
{
	this->setX(this->getX() + (this->getSpeed() * (this->getAngle() == (float)90 ? 1 : -1)));
	return true;
}

std::vector<RType::IElement*>			Shot::collideWith(RType::IElement* elem)
{
	return std::vector<RType::IElement*>();
}