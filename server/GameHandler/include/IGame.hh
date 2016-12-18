#ifndef GAMEHANDLER_IGAME_HH
#define GAMEHANDLER_IGAME_HH

#include "GameScene.hh"
#include "Player.hh"

class IGame
{
	public :
	virtual ~IGame(){};
	virtual bool launch() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool end() = 0;
	virtual GameScene* getScene() const = 0;
	virtual void addPlayer(Player*) = 0;
	virtual bool isReady() const = 0;
};

#endif