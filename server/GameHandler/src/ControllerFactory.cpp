#include "ControllerFactory.hh"

ControllerFactory::ControllerFactory()
{
}

ControllerFactory::~ControllerFactory()
{
}

GameController* ControllerFactory::create(){
	GameController* controller = new GameController();
	return controller;
}
