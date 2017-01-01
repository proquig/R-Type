#pragma once

#include        "Monster.hh"
#include		"Bildo.hh"
#include		"Boss.hh"
#include		"Player.hh"
#include		"Shot.hh"
#include		"Decor.hh"


class ElementFactory
{
private:
	unsigned int _elementId;

public:
	ElementFactory();
	~ElementFactory();
  	unsigned int newID();

public:

	RType::AElement*		create(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	Player*			createPlayer(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	RType::AElement*		createMonster(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	Shot*			createShot(uint32_t idFrom, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	Decor*			createDecor(uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey);

};

