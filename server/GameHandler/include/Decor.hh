#ifndef DECOR_HH_
#define DECOR_HH_

#include "GameElement.hpp"

class Decor : public GameElement
{
	public:
	Decor(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	~Decor();

	std::vector<IElement*>					collideWith(IElement*);
};

#endif