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
	game->addPlayer(controller->getElementFactory().createPlayer(50, 50, 50, 10, 10, 10, 0, 2));
	game->addPlayer(controller->getElementFactory().createPlayer(500, 500, 50, 10, 10, 10, 0, 2));
	game->addPlayer(controller->getElementFactory().createPlayer(5, 5, 50, 10, 10, 10, 0, 2));
	game->addPlayer(controller->getElementFactory().createPlayer(25, 25, 50, 10, 10, 10, 0, 2));

	std::cout << "game is ready : size =" << game->getScene()->getMap().size() << std::endl;
//	parser.parseTitle();
//	parser.parsePlayer();
//	for (IElement* elem : parser.getLine())
//	{
//		if (elem->getType() == AElement::PLAYER)
//			game->addPlayer((Player*)elem);
//	}
	return controller;
}
