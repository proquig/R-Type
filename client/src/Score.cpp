#include	"Score.hh"
#include	"SFMLSprite.hh"

void		Score::loadSprites(GLib lib)
{
	switch (lib)
	{
	case SFML:
		this->sprite = new SFMLSprite("./../../client/media/GAME-Assets/score.png");
		break;
	}
	_str = "Score : 0";
	this->sprite->addRessource("DEFAULT", std::vector<Cut *>
	{
		new Cut(0, 0, 900, 40)
	});
	_txt.setPosition(sf::Vector2f(100, 425));
	_txt.setCharacterSize(_fontSize);
	_txt.setFont(_font);
	this->animation = "DEFAULT";
	this->coords->x = 0;
	this->coords->y = 414;
	this->sprite->setAnimation(this->animation, this->coords, 0.89);
	return;
}

void	Score::print(void * window)
{
	if (_isReady)
	{
		this->sprite->print(window);
		((sf::RenderWindow *)window)->draw(_txt);
	}
	return;
}

void	Score::move(int _x, int _y, float _angle, int _speed)
{
	//std::cout << "_x = " << _x << " _y = " << _y << std::endl;
	this->coords->x = _x;
	this->coords->y = _y;
	this->angle = _angle;
	//this->speed = _speed;
	return;
}

void	Score::destroy()
{
	return;
}

/////////////////////////////////////////////////////////////////
// SETTERS
/////////////////////////////////////////////////////////////////

void	Score::setId(unsigned int _id)
{
	this->id = _id;
	return;
}

void	Score::setAnimation(std::string _animation)
{
	this->animation = _animation;
	return;
}

void	Score::setSize(Coords *_size)
{
	this->size = _size;
	return;
}

void	Score::setFont(std::string path)
{
	_isReady = true;
	if (!_font.loadFromFile(path))
	{
		_fontPath = path;
		_isReady = false;
	}
	return;
}

void	Score::setFontSize(int size)
{
	_fontSize = size;
	return;
}

void	Score::setMaxLength(int len)
{
	_maxLen = len + 39;
	return;
}

void	Score::setString(std::string str)
{
	_str = "Score : " + str;
	_txt.setString(_str);
	return;
}

void	Score::rmString()
{
	_str = "Score : 0";
	return;
}

/////////////////////////////////////////////////////////////////
// GETTERS
/////////////////////////////////////////////////////////////////

std::string Score::getString() const
{
	return (_str);
}
