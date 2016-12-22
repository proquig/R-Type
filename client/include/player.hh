#ifndef PLAYER_HH__
# define PLAYER_HH__

# include "element.hh"

class Player : public AElement
{

	std::string		skin;

public:

	enum Color
	{
		CYAN = 0,
		VIOLET,
		GREEN,
		RED,
		BLUE
	};

	Player(Color);

	void	loadSprites(GLib);
	void	print(void *);
	void	move(int, int, float, int);
	void	destroy();

};

#endif /* !PLAYER_HH__ */