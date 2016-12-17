#include "SFMLSprite.hh"
/*	*/
//	Private Functions
/*	*/
void				SFMLSprite::init()
{
	//_delta = _clock.restart();
	std::cout << "isAnimated = " << _isAnimated << std::endl;
	//_isAnimated = false;
	if (_tex.loadFromFile(_path))
	{
		std::cout << "Texture loaded." << std::endl;
	}
	//Generation du sprite courrant a partir du path
	std::cout << "init" << std::endl;
	return;
}

void				SFMLSprite::update()
{
	std::cout << "_isAnimated = " << _isAnimated << " _isOver = " << _isOver << std::endl;
	_delta += _clock.restart();
	if (!_isAnimated)
	{
		_spr = sf::Sprite(_tex);
		_spr.setTextureRect(_anim[_name]->at(0));
	}
	if (_isAnimated && !_isOver)
	{
		std::cout << "Delta = " << _delta.asMilliseconds() << "AnimTime = " << _animTime.asMilliseconds() << "cnt = " << _cnt << std::endl;
		if (_delta >= _animTime)
		{
			_cnt++;
			_delta = sf::seconds(0);
			if (_cnt >= _currAnim->size())
			{
				std::cout << "Reseting cnt" << std::endl;
				if (_loop)
					_cnt = 0;
				else
				{
					std::cout << "ou ici" << std::endl;
					_cnt = 0;
					_isOver = true;
				}
			}
		}
		_spr.setTexture(_tex);
		sf::IntRect rect = _currAnim->at(_cnt);
		_spr.setTextureRect(rect);
	}
	return;
}

void				SFMLSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isAnimated == true)
	{
		target.draw(_spr, states);
	}
	else
	{
		target.draw(_spr, states);
	}
	std::cout << "draw" << std::endl;
	return;
}


////////////////////////////////////////////////
//	Public Functions
////////////////////////////////////////////////

void				SFMLSprite::addRessource(std::string name, const std::vector<Cut *> pieces)
{
	//Add une suite d'element a jouer
	std::vector<sf::IntRect> *vect = new std::vector<sf::IntRect>();

	for (Cut *c : pieces)
	{
		vect->push_back(sf::IntRect(c->begin.x, c->begin.y, c->end.x, c->end.y));
	}
	_anim[name] = vect;
	return;
}

void					SFMLSprite::print(void *_window)
{
	sf::RenderWindow	*window = (sf::RenderWindow *)_window;

	update();
	if (_isAnimated == true)
	{
		std::cout << "Animation" << std::endl;
		window->draw(_spr);
	}
	else
	{
		window->draw(_spr);
	}
	std::cout << "print" << std::endl;
	return;
}

void				SFMLSprite::setAnimation(std::string name, Coords *pos, Coords *size)
{
	std::cout << "SETANIMATION" << std::endl;
	_name = name;
	_currAnim = _anim[name];
	_pos = std::make_pair(pos->x, pos->y);
	_size = std::make_pair(size->x, size->y);
	std::cout << "curranima -> size = " << _currAnim->size() << std::endl;
	init();
	return;
}

bool				SFMLSprite::isOver(void) const
{
	return (_isOver);
}

bool				SFMLSprite::getLoop() const
{
	return (_loop);
}

void				SFMLSprite::setLoop(bool val)
{
	_loop = val;
	return;
}

void				SFMLSprite::setAnimTime(float time)
{
	_animTime = sf::milliseconds(time);
	return;
}

bool				SFMLSprite::getAnimated() const
{
	return (_isAnimated);
}

void				SFMLSprite::setAnimated(bool val)
{
	_isAnimated = val;
	if (val)
	{
		_isOver = false;
	}
	else
	{
		_isOver = true;
	}
}