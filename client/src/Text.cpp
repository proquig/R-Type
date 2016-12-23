#include	"Text.hh"
#include	"SFMLSprite.hh"

void		Text::loadSprites(GLib lib)
{
	return;
}

void	Text::print(void * window)
{
	this->size->x = 50;
	this->size->y = 50;
	_txt.setCharacterSize(_fontSize);
	_txt.setFont(_font);
	_txt.setString(_str);
	return;
}

void	Text::move(int _x, int _y, float _angle, int _speed)
{
	this->coords->x = _x;
	this->coords->y = _y;
	this->angle = _angle;
	this->speed = _speed;
	return;
}

void	Text::destroy()
{
	return;
}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Text::setId(unsigned int _id)
{
	this->id = _id;
	return;
}

void	Text::setAnimation(std::string _animation)
{
	this->animation = _animation;
	return;
}

void	Text::setSize(Coords *_size)
{
	this->size = _size;
	return;
}

void	Text::setFont(std::string path)
{
	if (!_font.loadFromFile(path))
	{
		std::cout << "Couldn't load file. Not displaying this element" << std::endl;
		_fontPath = path;
		_isReady = false;
	}
	return;
}

void	Text::setFontSize(int size)
{
	_fontSize = size;
	return;
}

void	Text::setMaxLength(int len)
{
	_maxLen = len;
}

void	Text::setString(std::string str)
{
	_str = str;
}