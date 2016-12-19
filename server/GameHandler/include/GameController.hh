#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			"IObserver.hpp"
#include			"CollisionHandler.hh"
#include			"IGame.hh"
#include			"File.hh"
#include			"ElementFactory.hh"

class ISocket;
class ITimer;

class GameController : public IObserver
{
private:
	ElementFactory	_elemFact;
	CollisionHandler _collisionHandler;
	IGame*			_game;
	File*			_file;
	int				_clock;
  ISocket *_socket;
  ITimer *_timer;

public:
	GameController(IGame*, ISocket* = nullptr, ITimer* = nullptr);
	virtual ~GameController();

	void				handleCollisions();
	void				setGame(IGame*);
	bool				initGame(File*);
	void				startGame();
  virtual void update(int);
	virtual void update(IObservable*, int);
	ElementFactory&		getElementFactory();
  virtual ISocket* getSocket();
};

#endif