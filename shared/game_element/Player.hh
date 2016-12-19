#ifndef PLAYER_HH_
#define PLAYER_HH_

#include		"GameElement.hpp"

class Player : public GameElement
{
	private:
	bool		_alive;

	public:
  	Player();
	Player(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	~Player();
	std::vector<IElement*>					collideWith(IElement* elem);
	void	kill();
};
#endif