#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			"CollisionHandler.hh"
#include			"IObserver.hpp"
#include			"IGame.hh"
#include			"File.hh"
#include			"ElementFactory.hh"
#include			"Parser.hh"

class ISocket;
class ITimer;

#define		BASE_TICK	10;

class GameController : public IObserver
{
private:
	ElementFactory	_elemFact;
	CollisionHandler _collisionHandler;
	IGame*			_game;
	File*			_file;
	int				_clock;
  	ISocket 		*_socket;
  	ITimer 			*_timer;
	int				_delta;
	int				_tick;

public:
	GameController(IGame*, ISocket* = nullptr, ITimer* = nullptr);
	virtual ~GameController();

	void				handleCollisions();
	void				setGame(IGame*);
	bool				initGame(File*);
	void				startGame();
	int					getDelta() const;
	void				setDelta(int);
	int					getTick() const;
	virtual void		update(int);
	virtual void		update(IObservable*, int);
	ElementFactory&		getElementFactory();
  virtual ISocket*		getSocket();
	IGame*				getGame() const;
};

#endif