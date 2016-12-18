#ifndef PLAYER_HH__
# define PLAYER_HH__

# include "element.hh"

class Player : public AElement
{

public:

	void	update(AElement *);
	void	loadSprites(GLib);
	void	print(void *);
	void	move(Coords *);
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

#endif /* !PLAYER_HH__ */