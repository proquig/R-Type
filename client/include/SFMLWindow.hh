#ifndef SFML_WINDOW_HH__
# define SFML_WINDOW_HH__

# include <SFML/Graphics.hpp>
# include "window.hh"

class SFMLWindow : public AWindow
{

	sf::RenderWindow	*window;

public:

	SFMLWindow(int _w, int _h, std::string _name) : AWindow(_w, _h, _name) {}

	void	init(void);

	int		getWidth(void);
	int		getHeight(void);

};

#endif /* !SFML_WINDOW_HH__ */