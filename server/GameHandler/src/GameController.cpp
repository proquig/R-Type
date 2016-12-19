#include "GameController.hh"

GameController::GameController(IGame* game) : _collisionHandler(1920, 1080)
{
	_game = game;
}

GameController::~GameController()
{}

void			GameController::setGame(IGame* game)
{
	_game = game;
}

bool			GameController::initGame(File* file)
{
	if (_game == NULL)
	return false;
}

void			GameController::startGame()
{
	if (_game != NULL)
	_game->launch();
}

void			GameController::handleCollisions()
{
	std::vector<int>			destructElementId;
	std::vector<IElement*>		aEntity;

	aEntity = _collisionHandler.foundCollisions(_game->getScene()->getMap(), &destructElementId);
	for (std::vector<IElement *>::iterator it = aEntity.begin(); it != aEntity.end(); ++it)
	{
		std::cout << "Collision on entity " << (*it)->getId() << std::endl;
		_game->getScene()->getMap().push_back((*it));
	}
	for (std::vector<int>::iterator it = destructElementId.begin(); it != destructElementId.end(); ++it)
	{
		//sendDestructElement((*it));
	}
}

void GameController::update(IObservable *, int)
{

}

