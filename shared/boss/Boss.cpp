//
// Created by cloque_b on 30/12/16.
//

#include "Boss.hh"

Boss::Boss(uint32_t idFrom, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed, ElementFactory *factory)
        : GameElement::GameElement(idFrom, factory->newID(), type, x, y, hp, sizex, sizey, damage, angle, speed)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

Boss::Boss(uint16_t x, uint16_t y, ElementFactory *factory) :
        GameElement::GameElement(-1, (factory != nullptr ? factory->newID() : 0), RType::BOSS, x, y, 100, 10, 200, 1, 0, 10)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

Boss::~Boss()
{
}

std::vector<RType::IElement*>			 Boss::collideWith(RType::IElement* elem)
{
    if (elem->getType() == RType::DECOR)
        if (elem->getX() == this->_x && elem->getY() == this->_y ||
            this->_x == 0 && this->_y == 0)
            _direction = !_direction;
    return std::vector<RType::IElement*>();
}

bool    Boss::move()
{
    return (false);
}

Shot                            *Boss::shot()
{
    if (_mov == 10)
        _mov = 0;
    _mov++;
    if (_factory)
        return ((Shot *) _factory->create(this->_id, -1, RType::MISSILE, this->_x, this->_y + _mov, 10, 10, 10, 10, -90, 12));
    return nullptr;
}


RType::IElement *NewBoss(uint16_t x, uint16_t y, ElementFactory *factory) {
    RType::IElement *boss = new Boss(x, y, factory);
    return boss;
}

void destroyBoss(RType::IElement *element)
{
    if (element)
        delete element;
}

extern "C" {
#ifdef RT_UNIX
Dictionary getDictionary(void) {
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewBoss;
    (*dict)["destroy"] = (void *) &destroyBoss;
    return (dict);
}

#elif RT_WIN
__declspec(dllexport) Dictionary	__cdecl getDictionary(void)
{
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewBoss;
    (*dict)["destroy"] = (void *) &destroyBoss;
    return (dict);
}

#endif
}