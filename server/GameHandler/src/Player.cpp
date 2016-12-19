#include "Player.hh"

Player::Player(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed) : GameElement::GameElement(idFrom, id, type, x, y, hp, sizex, sizey, damage, angle, speed)
{
}

std::vector<IElement*>					Player::collideWith(IElement* elem)
{
	if (elem->getType() == AElement::PLAYER)
	{
		std::cout << "Collision between player " << _id << " and player " << elem->getId() << std::endl;
		std::cout << "HP=" << _hp << std::endl;
	}
	if (elem->getType() == AElement::DECOR)
	{
		_hp = 0;
	}
	return std::vector<IElement*>();
}
