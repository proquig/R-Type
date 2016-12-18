#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			"CollisionHandler.hh"
#include			"IGame.hh"
#include			"File.hh"

class GameController {
private:

	CollisionHandler _collisionHandler;
	IGame*			_game;
	File*			_file;
	int				_clock;

public:
	GameController(IGame*);
	~GameController();

	void				handleCollisions();
	void				setGame(IGame*);
	bool				initGame(File*);
	void				startGame();
};

#endif