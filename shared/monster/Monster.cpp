//
// Created by cloque_b on 19/12/16.
//

#include <Shot.hh>
#include "Monster.hh"

Monster::Monster(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed)
        : GameElement::GameElement(idFrom, id, type, x, y, hp, sizex, sizey, damage, angle, speed)
{
    _direction = false;
}

Monster::~Monster()
{
}

std::vector<IElement*>			 Monster::collideWith(IElement* elem)
{
    if (elem->getType() == AElement::DECOR)
        _direction = true;
    return std::vector<IElement*>();
}

bool    Monster::move()
{
    _direction ? this->_y++ : this->_y--;
    return _y % 3 != 0;
}


Shot                            *Monster::shot()
{
    return factory.createShot(this->_id, this->_x, this->_y, 1, 1, 1, 180, 5);
}