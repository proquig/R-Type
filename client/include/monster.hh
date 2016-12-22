#ifndef MONSTER_HH__
# define MONSTER_HH__

# include "element.hh"

class Monster : public AElement
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

	//////////////////////////////////////////////
	// GETTERS
	//////////////////////////////////////////////

	unsigned int	getId() const;
	Coords *		getCoords(void) const;
	Coords *		getSize(void) const;
	std::string		getAnimation(void) const;

};

#endif /* !MONSTER_HH__ */