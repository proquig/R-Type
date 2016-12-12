#ifndef SFML_SPRITE_HH__
# define SFML_SPRITE_HH__

# include <SFML/Graphics.hpp>
# include "SFMLWindow.hh"
# include "sprite.hh"

class SFMLSprite : public ASprite
{

	sf::RenderWindow	*window;
	sf::Texture			*texture;
	sf::Sprite			*sprite;

public:

	SFMLSprite(std::string _path, Coords *_begin, Coords *_end, sf::RenderWindow *_window)
		: ASprite(_path, _begin, _end), window(_window) {}

	void	load(void);
	void	print(Coords *, float);
	void	free(void);
};

#endif /* !SFML_SPRITE_HH__ */
