//
// Created by cloque_b on 19/12/16.
//

#ifndef R_TYPE_MONSTER_HH
#define R_TYPE_MONSTER_HH



#include "../game_element/Shot.hh"
#include "../../server/GameHandler/include/ElementFactory.hh"

class Monster : public GameElement
{
private:
    bool                _direction;
    ElementFactory      factory;

public:
    Monster(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
    ~Monster();

    std::vector<IElement*>					collideWith(IElement*);

    bool                                    move();
    Shot                                    *shot();
};


#endif //R_TYPE_MONSTER_HH
