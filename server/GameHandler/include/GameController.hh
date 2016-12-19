#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			"IObserver.hpp"
#include			"CollisionHandler.hh"
#include			"IGame.hh"
#include			"File.hh"
#include			"ElementFactory.hh"

class GameController : public IObserver
{
private:
	ElementFactory	_elemFact;
	CollisionHandler _collisionHandler;
	IGame*			_game;
	File*			_file;
	int				_clock;

public:
	GameController(IGame*);
	virtual ~GameController();

	void				handleCollisions();
	void				setGame(IGame*);
	bool				initGame(File*);
	void				startGame();
	virtual void update(IObservable*, int);
	ElementFactory&		getElementFactory();
};

#endif