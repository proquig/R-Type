#include "ControllerFactory.hh"

ControllerFactory::ControllerFactory()
{
	_gameId = 0;
}

ControllerFactory::~ControllerFactory()
{
}

GameController* ControllerFactory::create(File *file){
	
	Parser parser = (*new Parser(file));
	IGame*	game = new Game(_gameId++);
	GameController* controller = new GameController(game);

	game->addPlayer(new Player(0, 1, AElement::PLAYER, 10, 10, 50, 15, 15, 10, 0, 2));
	game->addPlayer(new Player(0, 2, AElement::PLAYER, 10, 50, 50, 15, 15, 10, 0, 2));
	game->addPlayer(new Player(0, 3, AElement::PLAYER, 100, 50, 50, 15, 15, 10, 0, 2));
	game->addPlayer(new Player(0, 4, AElement::PLAYER, 100, 50, 50, 15, 15, 10, 0, 2));

//	parser.parseTitle();
//	parser.parsePlayer();
//	for (IElement* elem : parser.getLine())
//	{
//		if (elem->getType() == AElement::PLAYER)
//			game->addPlayer((Player*)elem);
//	}
	return controller;
}
