#ifndef SHIP_HH__
# define SHIP_HH__

# include "element.hh"

class Ship : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);
};

#endif /* !SHIP_HH__ */