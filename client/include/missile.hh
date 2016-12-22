#ifndef MISSILE_HH__
# define MISSILE_HH__

# include "element.hh"

class Missile : public AElement
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

#endif /* !MISSILE_HH__ */