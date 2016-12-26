#include "Player.hh"

Player::Player()
{
  this->_type = RType::PLAYER;
}

Player::Player(uint32_t idFrom, uint32_t id, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed) : GameElement::GameElement(idFrom, id, RType::PLAYER, x, y, hp, sizex, sizey, damage, angle, speed)
{
	_alive = true;
}

Player::Player(struct sockaddr *addr)
{
  this->_type = RType::PLAYER;
  this->_addr = addr;
}

Player::~Player()
{
}

void	Player::kill()
{
	_alive = false;
}

std::vector<RType::IElement*>					Player::collideWith(RType::IElement* elem)
{
	if (elem->getType() == RType::PLAYER)
	{
		std::cout << "Collision between player " << _id << " and player " << elem->getId() << std::endl;
		std::cout << "HP=" << _hp << std::endl;
	}
	if (elem->getType() == RType::DECOR)
	{
		std::cout << "Player " << _id << " died by collide with wall " << elem->getId() << std::endl;
		_hp = 0;
	}
	return std::vector<RType::IElement*>();
}

struct sockaddr* Player::getAddr()
{
  return (this->_addr);
}

void Player::setAddr(struct sockaddr* addr)
{
  this->_addr = addr;
}
