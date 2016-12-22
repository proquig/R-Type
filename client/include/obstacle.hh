#ifndef OBSTACLE_HH__
# define OBSTACLE_HH__

# include "element.hh"

class Obstacle : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);
	void	move(int, int, float, int);
	void	destroy();

	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	void			setId(unsigned int);
	void			setAnimation(std::string);
	void			setSize(Coords *);

};

#endif /* !OBSTACLE_HH__ */