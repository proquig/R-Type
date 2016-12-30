//
// Created by cloque_b on 30/12/16.
//

#include "Bildo.hh"

Bildo::Bildo(uint32_t idFrom, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed, ElementFactory *factory)
        : GameElement::GameElement(idFrom, factory->newID(), type, x, y, hp, sizex, sizey, damage, angle, speed)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

Bildo::Bildo(uint16_t x, uint16_t y, ElementFactory *factory) :
        GameElement::GameElement(-1, (factory != nullptr ? factory->newID() : 0), RType::MONSTER, x, y, 3, 10, 10, 1, 0, 10)
{
    _factory = factory;
    _direction = 1;
    _mov = 0;
}

Bildo::~Bildo()
{
}

std::vector<RType::IElement*>			 Bildo::collideWith(RType::IElement* elem)
{
    if (elem->getType() == RType::DECOR)
        if (elem->getX() == this->_x && elem->getY() == this->_y ||
            this->_x == 0 && this->_y == 0)
            _direction = !_direction;
    return std::vector<RType::IElement*>();
}

bool    Bildo::move()
{
    static int i = 0;

    if (i % 2 == 0) {
        this->_mov++;
        _direction = (uint8_t) (!(this->_mov % 5) ? -_direction : _direction);
        this->_y += 10 * _direction;
        this->_x -= 5 + i;
    } else {
        this->_mov++;
        this->_y += 10 * _direction;
        this->_x += 5;
    }
    return ((this->_mov % 3) != 0);
}


Shot                            *Bildo::shot()
{
    if (_factory)
        return ((Shot *) _factory->create(this->_id, -1, RType::MISSILE, this->_x, this->_y, 10, 10, 10, 10, -90, 12));
    return nullptr;
}


RType::IElement *NewBildo(uint16_t x, uint16_t y, ElementFactory *factory) {
    RType::IElement *bildo = new Bildo(x, y, factory);
    return bildo;
}

void destroyBildo(RType::IElement *element)
{
    if (element)
        delete element;
}

extern "C" {
#ifdef RT_UNIX
Dictionary getDictionary(void) {
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewBildo;
    (*dict)["destroy"] = (void *) &destroyBildo;
    return (dict);
}

#elif RT_WIN
__declspec(dllexport) Dictionary	__cdecl getDictionary(void)
{
    Dictionary dict = new std::map<std::string, void *>;
    (*dict)["new"] = (void *) &NewBildo;
    (*dict)["destroy"] = (void *) &destroyBildo;
    return (dict);
}

#endif
}