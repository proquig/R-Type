//
// Created by cloque_b on 19/12/16.
//

#include "Monster.hh"

Monster::Monster(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed) : GameElement::GameElement(idFrom, id, type, x, y, hp, sizex, sizey, damage, angle, speed)
{
}

Monster::~Monster()
{
}

std::vector<IElement*>			Monster::collideWith(IElement* elem)
{
    return std::vector<IElement*>();
}