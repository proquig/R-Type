//
// Created by cloque_b on 30/12/16.
//

#include "C3PO.hh"

C3PO::C3PO(uint32_t idFrom, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed, ElementFactory *factory)
        : GameElement::GameElement(idFrom, factory->newID(), type, x, y, hp, sizex, sizey, damage, angle, speed)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

C3PO::C3PO(uint16_t x, uint16_t y, ElementFactory *factory) :
        GameElement::GameElement(-1, (factory != nullptr ? factory->newID() : 0), RType::C3PO, x, y, 3, 10, 10, 1, 0, 10)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

C3PO::~C3PO()
{
}

std::vector<RType::IElement*>			 C3PO::collideWith(RType::IElement* elem)
{
    if (elem->getType() == RType::DECOR)
        if (elem->getX() == this->_x && elem->getY() == this->_y ||
            this->_x == 0 && this->_y == 0)
            _direction = !_direction;
    return std::vector<RType::IElement*>();
}

bool    C3PO::move()
{
    this->_x += _direction;
    _direction+=_direction;
    return (true);
}


Shot                            *C3PO::shot()
{
    if (_factory)
        return ((Shot *) _factory->create(this->_id, -1, RType::MISSILE, this->_x, this->_y, 10, 10, 10, 10, -90, 12));
    return nullptr;
}


RType::IElement *NewC3PO(uint16_t x, uint16_t y, ElementFactory *factory) {
    RType::IElement *monster= new C3PO(x, y, factory);
    return monster;
}

void destroyC3PO(RType::IElement *element)
{
    if (element)
        delete element;
}

extern "C" {
#ifdef RT_UNIX
Dictionary getDictionary(void) {
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewC3PO;
    (*dict)["destroy"] = (void *) &destroyC3PO;
    return (dict);
}

#elif RT_WIN
__declspec(dllexport) Dictionary	__cdecl getDictionary(void)
{
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewC3PO;
    (*dict)["destroy"] = (void *) &destroyC3PO;
    return (dict);
}

#endif
}