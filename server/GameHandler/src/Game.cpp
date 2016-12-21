#include "Game.hh"


Game::Game(int id)
{
	_id = id;
	_gameScene = new GameScene(*(new Rectangle(1920 / 2, 1080 / 2, 1920, 1080)));
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

GameScene*		Game::getScene() const
{
	return _gameScene;
}

void			Game::addPlayer(Player* player)
{
	_players.push_back(player);
	_gameScene->addElem(player);
}

int				Game::isReady() const
{
	if (_players.size() < 5 && _players.size() > 0 && _gameScene->getMap().size() >= _players.size())
		return _players.size();
	return -1;
}

void			Game::display() const
{
	for (IElement* elem : _gameScene->getMap())
	{
		std::cout << elem->getId() << "(" << elem->getType() << ")" << ":" << elem->getX() << "/" << elem->getY() << "/" << elem->getSizeX() << "/" << elem->getSizeY() << "|||" << std::endl;
	}
}