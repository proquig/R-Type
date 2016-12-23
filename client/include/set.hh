#ifndef SET_HH__
# define SET_HH__

# include "element.hh"

class Set : public AElement
{

	std::string					land;
	std::chrono::milliseconds	tic;

public:

	enum Land {
		WASTE
	};

	Set(Land);

	void	loadSprites(GLib);
	void	print(void *);
};

#endif /* !SET_HH__ */