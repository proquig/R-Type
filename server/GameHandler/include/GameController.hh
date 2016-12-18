#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			"CollisionHandler.hh"
#include			"IGame.hh"

class GameController {
private:

	CollisionHandler _collisionHandler;
	IGame*			_game;

public:
	GameController();
	~GameController();

	void				handleCollisions();
	void				setGame(IGame*);
};

#endif