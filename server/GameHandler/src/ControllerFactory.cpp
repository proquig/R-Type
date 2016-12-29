#include "ControllerFactory.hh"
#include "Parser.hh"
#include "Game.hh"
#include "GameController.hh"

ControllerFactory::ControllerFactory()
{
	_gameId = 0;
}

ControllerFactory::~ControllerFactory()
{
}

GameController* ControllerFactory::create(File *file, ISocket* socket, ITimer* timer)
{
	
	IGame*	game = new Game(_gameId++, *(new Rectangle(1920 / 2, 1080 / 2, 1920, 1080)));
	GameController* controller = new GameController(game, socket, timer);
	controller->initGame(file);
	return controller;
}
