#include 		"GameHandler.hh"


GameHandler::GameHandler() : _nbGm(0), _nbCtrl(0)
{
}

GameHandler::~GameHandler()
{
}

std::map<int, IGame*> 			GameHandler::getGames() const
{
	return _games;
}

std::map<int, GameController*>	GameHandler::getControllers() const
{
	return _controllers;
}

bool							GameHandler::addGame(IGame* game)
{
	_games.insert(std::pair<int, IGame*>(_nbGm++, game));
	return true;
}

bool							GameHandler::addController(GameController* ctrl)
{
	_controllers.insert(std::pair<int, GameController*>(_nbCtrl++, ctrl));
	return true;
}
