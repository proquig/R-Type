#ifndef BOSS_HH__
# define BOSS_HH__

# include "element.hh"

class Boss : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);
};

#endif /* !BOSS_HH__ */