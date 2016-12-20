#ifndef R_TYPE_GAMEELEMENT_HPP_
#define R_TYPE_GAMEELEMENT_HPP_

#include <cstdint>
#include "AElement.hh"

class GameElement : public AElement
{
public:
	GameElement();
	GameElement(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	virtual ~GameElement();
};

#endif //R_TYPE_GAMEELEMENT_HPP_