#include "Game.hh"
#include "Rectangle.hh"


Game::Game(int id, const Rectangle& bounds) : _cadre(bounds)
{
	_id = id;
	_running = false;
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
	for (IElement* elem : _map)
	{
		std::cout << elem->getId() << "(" << elem->getType() << ")" << ":" << elem->getX() << "/" << elem->getY() << "/" << elem->getSizeX() << "/" << elem->getSizeY() << "|||" << std::endl;
	}
}

void			Game::updateScene()
{
	std::vector<IElement*>::iterator it = _map.begin();
	while (it != _map.end())
	{
		IElement* elem = (*it);
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
	std::vector<IElement*>::iterator it = _map.begin();
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

std::vector<IElement*>& Game::getMap()
{
	return _map;
}

void				Game::addElems(std::vector<IElement*> elems)
{
	for (IElement* g : elems)
	{
		_map.push_back(g);
	}
}

void				Game::addElem(IElement* elem)
{
	_map.push_back(elem);
}

const Rectangle&				Game::getCadre() const
{
	return _cadre;
}
