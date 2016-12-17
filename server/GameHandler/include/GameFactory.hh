#ifndef GAMEHANDLER_GAMEFACTORY_HH
#define GAMEHANDLER_GAMEFACTORY_HH

#include "Game.hh"

class GameFactory {
private:

public:
	GameFactory();
	~GameFactory();
	IGame* 	create();
	
};

#endif