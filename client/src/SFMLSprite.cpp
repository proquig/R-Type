#include "SFMLSprite.hh"
/*	*/
//	Private Functions
/*	*/
void				SFMLSprite::init()
{
	//_delta = _clock.restart();
	//std::cout << "isAnimated = " << _isAnimated << std::endl;
	//_isAnimated = false;
	if (_tex.loadFromFile(_path));
	if (_img.loadFromFile(_path))
	{
		_img.createMaskFromColor(sf::Color::Black);
	}
		//std::cout << "Texture loaded." << std::endl;
	//Generation du sprite courrant a partir du path
	return;
}

void				SFMLSprite::update()
{
	_delta += _clock.restart();
	if (!_isAnimated)
	{
		_tex.loadFromImage(_img);
		_spr = sf::Sprite(_tex);
		_spr.setTextureRect(_anim[_name]->at(0));
	}
	if (_isAnimated && !_isOver)
	{
		if (_delta >= _animTime)
		{
			_cnt++;
			_delta = sf::seconds(0);
			if (_cnt >= _currAnim->size())
			{
				if (_loop)
					_cnt = 0;
				else
				{
					_cnt = 0;
					_isOver = true;
				}
			}
		}
		_tex.loadFromImage(_img);
		//_spr.setTexture(_tex);
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
	_spr.setPosition(sf::Vector2f(_pos.first, _pos.second));
	if (_isAnimated == true)
	{
		window->draw(_spr);
	}
	else
	{
		window->draw(_spr);
	}
	return;
}

void				SFMLSprite::setAnimation(std::string name, Coords *pos, Coords *size)
{
	_name = name;
	_currAnim = _anim[name];
	_pos = std::make_pair(pos->x, pos->y);
	_size = std::make_pair(size->x, size->y);
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