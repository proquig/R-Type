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
	
	Parser parser = (*new Parser(file));
	IGame*	game = new Game(_gameId++);
	GameController* controller = new GameController(game, socket, timer);
	
//	parser.parseTitle();
//	parser.parsePlayer();
//	for (IElement* elem : parser.getLine())
//	{
//		if (elem->getType() == AElement::PLAYER)
//			game->addPlayer((Player*)elem);
//	}
	return controller;
}
