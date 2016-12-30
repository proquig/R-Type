#include	"Text.hh"
#include	"SFMLSprite.hh"

void		Text::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/button.png");
		break;
	}
	_str = "Enter an IP adress then press enter : \n";
	this->sprite->addRessource("DEFAULT", std::vector<Cut *>
	{
		new Cut(0, 0, 900, 506)
	});
	_txt.setPosition(sf::Vector2f(140, 330));
	return;
}

void	Text::print(void * window)
{
	if (_isReady)
	{
		this->animation = "DEFAULT";
		this->size->x = 0;
		this->size->y = 0;
		this->sprite->setAnimation(this->animation, this->coords, 1);
		this->sprite->print(window);
		this->size->x = 0;
		this->size->y = 0;
		_txt.setCharacterSize(_fontSize);
		_txt.setFont(_font);
		_txt.setString(_str);
		((sf::RenderWindow *)window)->draw(_txt);
	}
	return;
}

void	Text::move(int _x, int _y, float _angle, int _speed)
{
	//std::cout << "_x = " << _x << " _y = " << _y << std::endl;
	this->coords->x = _x;
	this->coords->y = _y;
	this->angle = _angle;
	//this->speed = _speed;
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
	_isReady = true;
	if (!_font.loadFromFile(path))
	{
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
	_maxLen = len + 39;
	return;
}

void	Text::setString(std::string str)
{
	//std::cout << "strlen() = " << _maxLen << " str = " << str << std::endl;
	if (str.size() < _maxLen && str.size() == 1 && (str.size() + _str.size()) < _maxLen)
		_str += str;
	return;
}

void	Text::rmString()
{
	_str = "Enter an IP adress then press enter : \n";
	return;
}

/////////////////////////////////////////////////////////////////
// GETTERS
/////////////////////////////////////////////////////////////////

std::string Text::getString() const
{
	return (_str);
}