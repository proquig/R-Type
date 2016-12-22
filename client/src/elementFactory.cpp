#include "element.hh"
#include "player.hh"
#include "monster.hh"
#include "missile.hh"
#include "obstacle.hh"
#include "set.hh"

AElement *					ElementFactory::create(unsigned int _id, ElementType type)
{
	static Player::Color	playerColor = Player::CYAN;
	AElement				*element;

	switch (type)
	{
	case PLAYER:
		element = new Player(playerColor);
		switch (playerColor) {
			case Player::CYAN:
				playerColor = Player::VIOLET;
				break;
			case Player::VIOLET:
				playerColor = Player::GREEN;
				break;
			case Player::GREEN:
				playerColor = Player::RED;
				break;
			case Player::RED:
				playerColor = Player::BLUE;
				break;
			default :
				playerColor = Player::CYAN;
				break;
		}
		break;
	case MONSTER:
		element = new Monster();
		break;
	case MISSILE:
		element = new Missile();
		break;
	case OBSTACLE:
		element = new Obstacle(Obstacle::DEFAULT);
		break;
	case SET:
		element = new Set();
		break;

	default:
		// unknown TO-DO
		break;
	}
	element->setId(_id);
	return (element);
}