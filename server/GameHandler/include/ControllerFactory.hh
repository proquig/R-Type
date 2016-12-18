#ifndef GAMEHANDLER_CONTROLLERFACTORY_HH
#define GAMEHANDLER_CONTROLLERFACTORY_HH

#include	"GameController.hh"
#include	"Game.hh"
#include	"Parser.hh"

class ControllerFactory {
private:
	int		_gameId;

public:
	ControllerFactory();
	~ControllerFactory();
	GameController* create(File *file);
};

#endif