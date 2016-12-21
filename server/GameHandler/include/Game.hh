#ifndef GAMEHANDLER_GAME_HH
#define GAMEHANDLER_GAME_HH

#include "IGame.hh"
#include "GameScene.hh"
#include "File.hh"

class Game : public IGame {

private:
	GameScene*					_gameScene;
	std::vector<Player*>		_players;
	int							_id;
	bool						_running;

public:
	Game(int);
	~Game();
	virtual bool launch();
	virtual bool stop();
	virtual bool pause();
	virtual bool end();
	virtual void addPlayer(Player*);
	virtual GameScene* getScene() const;
	virtual int isReady() const;
	virtual bool isRunning() const;
	virtual void display() const;
};

#endif