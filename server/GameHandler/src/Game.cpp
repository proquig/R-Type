#include "Game.hh"
#include "Rectangle.hh"


Game::Game(int id, const Rectangle& bounds) : _cadre(bounds)
{
  this->_id = id;
  this->_running = false;
  this->_score = 0;
}

Game::~Game()
{
}

bool			Game::launch()
{
	_running = true;
	return true;
}

bool			Game::stop()
{
	_running = false;
	return true;
}

bool			Game::pause()
{
	_running = false;
	return true;
}

bool			Game::end()
{
	_running = false;
	return true;
}

bool			Game::isRunning() const
{
	return _running;
}

void			Game::addPlayer(Player* player)
{
	_players.push_back(player);
	addElem(player);
}

int				Game::isReady() const
{
	if (_players.size() < 5 && _players.size() > 0 && _map.size() >= _players.size())
		return _players.size();
	return -1;
}

void			Game::display() const
{
	for (RType::IElement* elem : _map)
	{
		std::cout << elem->getId() << "(" << elem->getType() << ")" << ":" << elem->getX() << "/" << elem->getY() << "/" << elem->getSizeX() << "/" << elem->getSizeY() << "|||" << std::endl;
	}
}

void			Game::updateScene()
{
	std::vector<RType::IElement*>::iterator it = _map.begin();
	while (it != _map.end())
	{
		RType::IElement* elem = (*it);
		if (!_cadre.isIn(*(new Rectangle(elem->getX(), elem->getY(), elem->getSizeX(), elem->getSizeY()))))
		{
			it = _map.erase(it);
		}
		else
			it++;
	}
}

void			Game::drawNewElem()
{
}

void			Game::deleteElem(int id)
{
	std::vector<RType::IElement*>::iterator it = _map.begin();
	while (it != _map.end())
	{
		if ((*it)->getId() == id)
		{
			it = _map.erase(it);
		}
		else
			it++;
	}
}

std::vector<RType::IElement*>& Game::getMap()
{
	return _map;
}

void				Game::addElems(std::vector<RType::IElement*> elems)
{
	for (RType::IElement* g : elems)
	{
		_map.push_back(g);
	}
}

void				Game::addElem(RType::IElement* elem)
{
  if (elem && !this->isPresent(elem))
	_map.push_back(elem);
}

bool 				Game::isPresent(RType::IElement* element)
{
  return (std::find(this->_map.begin(), this->_map.end(), element) != this->_map.end());
}

bool 				Game::deleteElem(RType::IElement* element)
{
  std::vector<RType::IElement*>::iterator	it;

  if ((it = std::find(this->_map.begin(), this->_map.end(), element)) == this->_map.end())
	return (false);
  this->_map.erase(it);
  return (true);
}

std::vector<RType::IElement*>::iterator Game::deleteElem(const std::vector<RType::IElement*>::iterator &it)
{
  return this->_map.erase(it);;
}

const Rectangle&				Game::getCadre() const
{
	return _cadre;
}

void Game::updateScore(uint16_t score)
{
  this->_score += score;
}

uint16_t Game::getScore() const
{
  return (this->_score);
}