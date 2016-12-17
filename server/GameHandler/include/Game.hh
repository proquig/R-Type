#ifndef GAMEHANDLER_GAME_HH
#define GAMEHANDLER_GAME_HH

#include "IGame.hh"
#include "GameScene.hh"

class Game : public IGame {

private:
	GameScene _gameScene;
	
public:
	Game();
	~Game();
	virtual bool launch();
	virtual bool stop();
	virtual bool pause();
	virtual bool end();
};

#endif