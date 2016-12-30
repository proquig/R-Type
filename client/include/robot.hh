#ifndef ROBOT_HH__
# define ROBOT_HH__

# include "element.hh"

class Robot : public AElement
{

public:

	void	loadSprites(GLib);
	void	print(void *);
};

#endif /* !ROBOT_HH__ */