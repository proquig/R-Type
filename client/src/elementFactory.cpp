#include "element.hh"
#include "player.hh"
#include "monster.hh"
#include "missile.hh"
#include "obstacle.hh"
#include "set.hh"

AElement *					ElementFactory::create(unsigned int _id, RType::eType type)
{
	static Player::Color	playerColor = Player::CYAN;
	AElement				*element = nullptr;

	switch (type)
	{
		case RType::PLAYER:
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
	case RType::MONSTER:
		element = new Monster();
		break;
	case RType::MISSILE:
		element = new Missile(Missile::DEFAULT);
		break;
	case RType::OBSTACLE:
		element = new Obstacle(Obstacle::DEFAULT);
		break;
	case RType::SET:
		element = new Set(Set::WASTE);
		break;

	default:
		// unknown TO-DO
		break;
	}
	if (element)
	{
		element->setId(_id);
		element->setType(type);
	}
	return (element);
}