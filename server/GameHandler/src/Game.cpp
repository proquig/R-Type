#include "Game.hh"


Game::Game()
{
	_gameScene = new GameScene();
}

Game::~Game()
{
}

bool			Game::launch()
{
	return true;
}

bool			Game::stop()
{
	return true;
}

bool			Game::pause()
{
	return true;
}

bool			Game::end()
{
	return true;
}

GameScene*		Game::getScene() const
{
	return _gameScene;
}