#ifndef SET_HH__
# define SET_HH__

# include "element.hh"

class Set : public AElement
{

	std::string	land;

public:

	enum Land {
		WASTE
	};

	Set(Land);

	void	loadSprites(GLib);
	void	print(void *);
	void	move(int, int, float, int);
	void	destroy();
};

#endif /* !SET_HH__ */