#ifndef SPRITE_HH__
# define SPRITE_HH__

# include "coords.hh"

class ISprite
{
public:
	virtual void	load(void) = 0;
	virtual void	print(Coords *, float) = 0;
	virtual void	free(void) = 0;
};

class ASprite
{
protected:

	std::string		path;

	////////////////////////////////////////
	// CUT
	////////////////////////////////////////

	Coords			*begin;
	Coords			*end;

public:

	ASprite(std::string _path, Coords *_begin, Coords *_end)
		: path(_path), begin(_begin), end(_end) {}
};

#endif /* !SPRITE_HH__ */