#include "SFMLSprite.hh"

void	SFMLSprite::addRessource(std::string name, const std::vector<Cut *> pieces)
{
	// name = nom de l'animation � jouer.
	// pieces = pi�ces n�c�ssaire � l'animation (dans l'ordre)
	//		1 pi�ce = sprite statique
}

void	SFMLSprite::setAnimation(std::string name, Coords *pos, Coords *size)
{
	// name = nom de l'animation � jouer.
	// pos = position coin superieur droit.
	// size = size.x = width; size.y = height
}

bool	SFMLSprite::isOver(void) const
{
	// Animation done
	return (true);
}