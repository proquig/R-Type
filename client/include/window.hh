#ifndef WINDOW_HH__
# define WINDOW_HH__

# include <iostream>

class IWindow
{

public:

	virtual void	init(void) = 0;

	/////////////////////////////////////////////////
	// GETTERS
	/////////////////////////////////////////////////

	virtual int		getWidth(void) = 0;
	virtual int		getHeight(void) = 0;

};

class AWindow : public IWindow
{

protected:

	int				width;
	int				height;
	std::string		name;

public:

	AWindow(int _w, int _h, std::string _name) : width(_w), height(_h), name(_name) {}

};

#endif /* !WINDOW_HH__ */