#ifndef MONSTER_HH__
# define MONSTER_HH__

# include "element.hh"

class Monster : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);

};

#endif /* !MONSTER_HH__ */