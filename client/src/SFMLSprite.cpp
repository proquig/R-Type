#include "SFMLSprite.hh"
/*	*/
//	Private Functions
/*	*/
void				SFMLSprite::init()
{
	_delta = _clock.restart();
	_loop = false;
	_isOver = true;
	_isAnimated = false;
	_tex.loadFromFile(_path);
	_pos = std::make_pair(0, 0);
	_size = std::make_pair(10, 10);
	//Generation du sprite courrant a partir du path
	return;
}

void				SFMLSprite::update()
{
	_delta += _clock.restart();
	if (!_isAnimated)
	{
		_spr = new sf::Sprite(_tex);
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
			_spr->setTexture(_tex);
			sf::IntRect rect = _currAnim->at(_cnt);
			_spr->setTextureRect(_currAnim->at(_cnt));
		}
	}
	return;
}

void				SFMLSprite::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	if (_isAnimated == true)
	{
		target.draw(*_spr, states);
	}
	else
	{
		target.draw(*_spr, states);
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

	window->draw(*_spr);
}

void				SFMLSprite::setAnimation(std::string name, Coords *pos, Coords *size)
{
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
	_delta = sf::seconds(time);
	return;
}