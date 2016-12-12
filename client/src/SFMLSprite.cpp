#include "SFMLSprite.hh"

void	SFMLSprite::addRessource(std::string name, const std::vector<Cut *> pieces)
{
	// name = nom de l'animation à jouer.
	// pieces = pièces nécéssaire à l'animation (dans l'ordre)
	//		1 pièce = sprite statique
}

void	SFMLSprite::setAnimation(std::string name, Coords *pos, Coords *size)
{
	// name = nom de l'animation à jouer.
	// pos = position coin superieur droit.
	// size = size.x = width; size.y = height
}

bool	SFMLSprite::isOver(void) const
{
	// Animation done
	return (true);
}