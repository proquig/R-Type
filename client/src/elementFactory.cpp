#include "element.hh"
#include "player.hh"
#include "monster.hh"
#include "missile.hh"
#include "obstacle.hh"
#include "set.hh"

AElement *	ElementFactory::create(unsigned int _id, ElementType type, std::string _animation, int _x, int _y, unsigned int _w, unsigned int _h)
{
	AElement	*element;

	switch (type)
	{

	case PLAYER:
		element = new Player();
		break;
	case MONSTER:
		element = new Monster();
		break;
	case MISSILE:
		element = new Missile();
		break;
	case OBSTACLE:
		element = new Obstacle();
		break;
	case SET:
		element = new Set();
		break;

	default:
		// unknown TO-DO
		break;
	}
	element->setId(_id);
	element->move(_x, _y);
	element->setSize(new Coords(_w, _h));
	element->setAnimation(_animation);
	return (element);
}