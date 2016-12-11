#ifndef SFML_WINDOW_HH__
# define SFML_WINDOW_HH__

# include <SFML/Graphics.hpp>
# include "window.hh"

class SFMLWindow : public AWindow
{

	sf::RenderWindow	*handler;
	sf::Event			event;

public:

	SFMLWindow(int _w, int _h, std::string _name) : AWindow(_w, _h, _name) {}

	void	run(WorkQueue<AElement *> *, WorkQueue<Event *> *);
	void	pollEvent(void);
	void	renderScene(void);
	void	render(void);

	void *	getHandler(void);
	int		getWidth(void);
	int		getHeight(void);

};

#endif /* !SFML_WINDOW_HH__ */