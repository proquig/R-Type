#ifndef MISSILE_HH__
# define MISSILE_HH__

# include "element.hh"

class Missile : public AElement
{

	std::string		skin;

public:

	enum Type {
		DEFAULT
	};

	Missile(Type);

	void	loadSprites(GLib);
	void	print(void *);

};

#endif /* !MISSILE_HH__ */