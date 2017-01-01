#ifndef GAMEHANDLER_GAMEHANDLER_HH
#define GAMEHANDLER_GAMEHANDLER_HH

#include <iostream>
#include <map>

class GameController;
class IGame;

class GameHandler
{
private:
	int								_nbGm;
	int								_nbCtrl;
	std::map<int, IGame*>			_games;
	std::map<int, GameController*>	_controllers;
	
public:
	GameHandler();
	virtual ~GameHandler();
	std::map<int, IGame*>			getGames() const;
	std::map<int, GameController*> 	getControllers() const;
	bool							addGame(IGame*);
	bool							addController(GameController*);
};

#endif