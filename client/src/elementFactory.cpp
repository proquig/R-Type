#include "element.hh"
#include "player.hh"
#include "monster.hh"
#include "missile.hh"
#include "obstacle.hh"
#include "set.hh"

AElement *	ElementFactory::create(ElementType type, std::string _animation, unsigned int _x, unsigned int _y, unsigned int _w, unsigned int _h)
{
	AElement	*element;

	switch (type)
	{

	case PLAYER:
		element = new Player();
		break;

		// Others ...

	default:
		// unknown TO-DO
		break;
	}
	element->move(new Coords(_x, _y));
	element->setSize(new Coords(_w, _h));
	element->setAnimation(_animation);
	return (element);
}