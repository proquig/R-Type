#include "player.hh"
#include "SFMLSprite.hh"

void	Player::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite(".\\media\\GAME-Assets\\r-typesheet42.gif");
		break;
	}

	this->sprite->addRessource("cyan_stay", std::vector<Cut *>{new Cut(0, 0, 50, 50)});
}

void	Player::print(void * window)
{
	std::cout << "Print player ..." << std::endl;
	this->sprite->setAnimation("cyan_stay", new Coords (0, 0), new Coords(50, 50));
	this->sprite->print(window);
}

void	Player::move(Coords *to)
{

}

void	Player::animate(std::string action)
{

}

void	Player::destroy()
{

}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Player::setId(unsigned int _id)
{
	this->id = _id;
}

/////////////////////////////////////////////////////////////////
// GETTERS
/////////////////////////////////////////////////////////////////

unsigned int	Player::getId(void) const
{
	return (this->id);
}