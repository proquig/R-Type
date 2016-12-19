#pragma once

#include		"Player.hh"
#include		"Shot.hh"

class ElementFactory
{
private:
	int		_elementId;

public:
	ElementFactory();
	~ElementFactory();

public:

	Player*			createPlayer(uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	Shot*			createShot(uint32_t idFrom, uint16_t x, uint16_t y, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
};

