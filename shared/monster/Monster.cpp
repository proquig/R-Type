//
// Created by cloque_b on 19/12/16.
//

#include "Monster.hh"

Monster::Monster(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed, ElementFactory *factory)
        : GameElement::GameElement(idFrom, id, type, x, y, hp, sizex, sizey, damage, angle, speed)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

Monster::Monster(uint32_t id, uint16_t x, uint16_t y, ElementFactory *factory) :
        GameElement::GameElement(-1, id, RType::MONSTER, x, y, 3, 10, 10, 1, 0, 10)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}


Monster::~Monster()
{
}

std::vector<RType::IElement*>			 Monster::collideWith(RType::IElement* elem)
{
    if (elem->getType() == RType::DECOR)
        if (elem->getX() == this->_x && elem->getY() == this->_y ||
                this->_x == 0 && this->_y == 0)
        _direction = !_direction;
    return std::vector<RType::IElement*>();
}

bool    Monster::move()
{
    //this->_mov = (uint8_t) ((this->_mov + 1) % 3);
    this->_mov++;
    _direction = (uint8_t) (!(this->_mov % 3) ? -_direction : _direction);
    this->_y += 10 * _direction;
    this->_x -= 5;
    return (this->_mov != 0);
}


Shot                            *Monster::shot()
{
//    return _factory->createShot(this->_id, this->_x, this->_y, 1, 1, 1, 180, 5);
    return ((Shot *) _factory->create(this->_id, -1, RType::MISSILE, this->_x, this->_y, 10, 10, 10, 10, 180, 8));
}


RType::IElement *NewMonster(uint32_t id, uint16_t x, uint16_t y, ElementFactory *factory) {
    RType::IElement *monster = new Monster(id, x, y, factory);
    return monster;
}

void destroyMonster(RType::IElement *element)
{
    if (element)
        delete element;
}

extern "C" {
#ifdef RT_UNIX
Dictionary getDictionary(void) {
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewMonster;
    (*dict)["destroy"] = (void *) &destroyMonster;
    return (dict);
}

#elif RT_WIN
__declspec(dllexport) Dictionary	__cdecl getDictionary(void)
{
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewMonster;
    (*dict)["destroy"] = (void *) &destroyMonster;
    return (dict);
}

#endif
}