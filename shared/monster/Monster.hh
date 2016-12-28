//
// Created by cloque_b on 19/12/16.
//

#ifndef R_TYPE_MONSTER_HH
#define R_TYPE_MONSTER_HH

#include "Shot.hh"
#include "ElementFactory.hh"
#include <iostream>
#include "../dlloader/include/DLDictionary.hh"

class ElementFactory;

class Monster : public GameElement
{
private:
    int8_t				_direction;
  	uint8_t				_mov;
    ElementFactory      *_factory;

public:
    Monster(uint32_t idFrom, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed, ElementFactory *factory);
    Monster(uint16_t x, uint16_t y, ElementFactory *factory);
    ~Monster();

    std::vector<IElement*>					collideWith(IElement*);

    bool                                    move();
    Shot                                    *shot();
};


#endif //R_TYPE_MONSTER_HH
