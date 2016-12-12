#ifndef SFML_SPRITE_HH__
# define SFML_SPRITE_HH__

# include <SFML/Graphics.hpp>
# include "SFMLWindow.hh"
# include "sprite.hh"

class SFMLSprite : public ASprite
{

public:

	SFMLSprite(std::string _path)
		: ASprite(_path) {}

	void	addRessource(std::string, const std::vector<Cut *>);

	/////////////////////////////////////////////////////////////////////////////
	// ANIMATION
	/////////////////////////////////////////////////////////////////////////////

	void	setAnimation(std::string, Coords *, Coords *);
	bool	isOver(void) const;
};

#endif /* !SFML_SPRITE_HH__ */
