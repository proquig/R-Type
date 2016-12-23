#ifndef OBSTACLE_HH__
# define OBSTACLE_HH__

# include "element.hh"

class Obstacle : public AElement
{	
	std::string	skin;

public:

	enum Skin {
		DEFAULT
	};

	Obstacle(Skin);

	void	loadSprites(GLib);
	void	print(void *);

};

#endif /* !OBSTACLE_HH__ */