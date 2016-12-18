#ifndef PLAYER_HH_
#define PLAYER_HH_

#include		"GameElement.hpp"

class Player : public GameElement
{
	public:
	Player();
	Player(uint32_t, uint32_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, uint16_t, float, char);

	std::vector<IElement*>					collideWith(IElement* elem);
};
#endif