#include "GameController.hh"

GameController::GameController() : _collisionHandler(1920, 1080)
{
}

GameController::~GameController()
{}

void			GameController::setGame(IGame* game)
{
	_game = game;
}

void			GameController::handleCollisions()
{
	std::vector<int>			destructElementId;
	std::vector<GameElement *>		aEntity;

	aEntity = _collisionHandler.foundCollisions(_game->getScene()->getMap(), &destructElementId);
	for (std::vector<GameElement *>::iterator it = aEntity.begin(); it != aEntity.end(); ++it)
		_game->getScene()->getMap().push_back((*it));
	for (std::vector<int>::iterator it = destructElementId.begin(); it != destructElementId.end(); ++it)
	{
		std::cout << (*it) << " needs to be destroy" << std::endl;
	}
	//sendDestructElement((*it));
}
