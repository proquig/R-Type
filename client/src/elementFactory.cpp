#include "element.hh"
#include "player.hh"
#include "monster.hh"
#include "missile.hh"
#include "obstacle.hh"
#include "set.hh"

AElement *	ElementFactory::create(ElementType type, unsigned int _x, unsigned int _y)
{
	AElement	*element;

	switch (type)
	{

	case PLAYER:
		element = new Player();
		break;

	default:
		// unknown TO-DO
		break;
	}
	element->move(new Coords(_x, _y));
	return (element);
}