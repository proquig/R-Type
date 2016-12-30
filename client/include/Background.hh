#ifndef BACKGROUND_HH__
# define BACKGROUND_HH__

# include "element.hh"

class Background : public AElement
{

	std::string					image;

public:

	enum Image {
		GAME_OVER
	};

	Background(Image);

	void	loadSprites(GLib);
	void	print(void *);
};

#endif /* !BACKGROUND_HH__ */