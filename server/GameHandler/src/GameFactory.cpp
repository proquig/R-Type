#include "GameFactory.hh"

GameFactory::GameFactory()
{
}

GameFactory::~GameFactory()
{
}

IGame*				GameFactory::create()
{
	IGame* game = new Game();
	return game;
}
