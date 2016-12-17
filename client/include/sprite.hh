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
	virtual void	print(void *window) = 0;
	
	/////////////////////////////////////////////////////////////////////////////
	// ANIMATION
	/////////////////////////////////////////////////////////////////////////////

	virtual void	setAnimation(std::string, Coords *, Coords *) = 0;
	virtual bool	isOver(void) const = 0;
	virtual bool	getAnimated() const = 0;
	virtual void	setAnimated(bool) = 0;
	virtual void	setAnimTime(float) = 0;
	virtual void	setLoop(bool) = 0;

};

class ASprite : public ISprite
{
protected:

	std::string		_path;
	bool			_isOver;
	bool			_isAnimated;
	bool			_loop;
	int				_cnt;

public:

	ASprite(std::string _path, bool loop = false, bool isOver = true, bool isAnim = false)
		: _path(_path), _loop(loop), _isOver(isOver), _isAnimated(isAnim) {_cnt = 0;}
};

#endif /* !SPRITE_HH__ */