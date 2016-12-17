#ifndef GAMEHANDLER_CONTROLLERFACTORY_HH
#define GAMEHANDLER_CONTROLLERFACTORY_HH

#include	"GameController.hh"

class ControllerFactory {
private:
public:
	ControllerFactory();
	~ControllerFactory();
	GameController* create();
};

#endif