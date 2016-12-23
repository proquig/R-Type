#ifndef MISSILE_HH__
# define MISSILE_HH__

# include "element.hh"

class Missile : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);

};

#endif /* !MISSILE_HH__ */