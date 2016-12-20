//
// Created by cloque_b on 19/12/16.
//

#ifndef R_TYPE_MONSTER_HH
#define R_TYPE_MONSTER_HH

#include	"IElement.hh"
#include    "GameElement.hpp"

class Monster : public GameElement
{
public:
    Monster(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
  virtual ~Monster();

    std::vector<IElement*>					collideWith(IElement*);
};


#endif //R_TYPE_MONSTER_HH
