#include "element.hh"
#include "player.hh"
#include "monster.hh"
#include "robot.hh"
#include "boss.hh"
#include "missile.hh"
#include "ship.hh"
#include "obstacle.hh"
#include "set.hh"
#include "Text.hh"
#include "Score.hh"
#include "Background.hh"

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
	case RType::BOSS:
		element = new Boss();
	case RType::BILDO:
		element = new Ship();
	case RType::MISSILE:
		element = new Missile(Missile::DEFAULT);
		break;
	case RType::OBSTACLE:
		element = new Obstacle(Obstacle::DEFAULT);
		break;
	case RType::SET:
		element = new Set(Set::WASTE);
		break;
	case RType::TEXT:
		element = new Text();
		((Text *)element)->setFont("./../../client/media/GAME-Assets/space.otf");
		((Text *)element)->setFontSize(20);
		((Text *)element)->setMaxLength(16);
		break;
	case RType::SCORE:
		element = new Score();
		((Score *)element)->setFont("./../../client/media/GAME-Assets/space.otf");
		((Score *)element)->setFontSize(17);
		((Score *)element)->setMaxLength(16);
		break;
	case RType::BACKGROUND:
		element = new Background(Background::GAME_OVER);
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