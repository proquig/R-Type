#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			"CollisionHandler.hh"

class GameController {
private:

	CollisionHandler _collisionHandler;

public:
	GameController();
	~GameController();

	void				handleCollisions();
};

#endif