#ifndef PLAYER_HH__
# define PLAYER_HH__

# include "element.hh"

class Player : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);
	void	move(Coords *);
	void	animate(std::string);
	void	destroy();

	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	void	setId(unsigned int);

	//////////////////////////////////////////////
	// GETTERS
	//////////////////////////////////////////////

	unsigned int	getId() const;

};

#endif /* !PLAYER_HH__ */