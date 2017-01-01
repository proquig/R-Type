#ifndef			SHOT_HH_
#define			SHOT_HH_

#include		"GameElement.hpp"

class Shot : public GameElement
{
	public:
	Shot(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	virtual ~Shot();
	virtual std::vector<RType::IElement*>					collideWith(RType::IElement* elem);
	virtual bool											move();
};

#endif