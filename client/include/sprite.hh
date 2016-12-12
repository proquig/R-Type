#ifndef SPRITE_HH__
# define SPRITE_HH__

# include <iostream>
# include <vector>
# include "coords.hh"

////////////////////////////////////////
// CUT
////////////////////////////////////////

struct Cut
{
	Coords	begin;
	Coords	end;

	Cut(unsigned int b_x, unsigned int b_y, unsigned int e_x, unsigned int e_y)
		: begin(Coords(b_x, b_x)), end(Coords(e_x, e_y)) {}

};

class ISprite
{
public:
	virtual void	addRessource(std::string, const std::vector<Cut *>) = 0;
	
	/////////////////////////////////////////////////////////////////////////////
	// ANIMATION
	/////////////////////////////////////////////////////////////////////////////

	virtual void	setAnimation(std::string, Coords *, Coords *) = 0;
	virtual bool	isOver(void) = 0;
};

class ASprite
{
protected:

	std::string		path;

public:

	ASprite(std::string _path)
		: path(_path) {}
};

#endif /* !SPRITE_HH__ */