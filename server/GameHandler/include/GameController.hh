#ifndef GAMEHANDLER_GAMECONTROLLER_HH
#define GAMEHANDLER_GAMECONTROLLER_HH

#include			<algorithm>
#include			"CollisionHandler.hh"
#include			"IObserver.hpp"
#include			"IGame.hh"
#include			"File.hh"
#include			"ElementFactory.hh"
#include			"Parser.hh"
#include			"DLManager.hh"

class ISocket;
class ITimer;

#define		BASE_TICK	10;

class GameController : public IObserver
{
private:
	enum bossState {
		NS,
		ALIVE,
		DEAD
	};

	ElementFactory	_elemFact;
	CollisionHandler _collisionHandler;
	IGame*			_game;
	File*			_file;
	int				_clock;
  	ISocket 		*_socket;
  	ITimer 			*_timer;
	int				_delta;
	int				_tick;
  	Dictionary*		_dicMonster;
  	Dictionary*		_dicBildo;
	Dictionary*		_dicBoss;
	Dictionary*		_dicC3PO;

private:
	Monster*		_monster;
  	Bildo*			_bildo;
	Boss*			_Boss;
	bool			_boss;

public:
	GameController(IGame*, ISocket* = nullptr, ITimer* = nullptr);
	virtual ~GameController();

  	void 				setDicMonster(Dictionary* dic);
	void 				setDicBildo(Dictionary* dic);
	void				setDicBoss(Dictionary *_dicBoss);
	void 				setDicC3PO(Dictionary *_dicC3PO);
	void				handleCollisions();
	void				setGame(IGame*);
	bool				initGame(File*);
	void				startGame();
	int					getDelta() const;
	void				setDelta(int);
	int					getTick() const;
	virtual void		update(int);
	virtual void		update(IObservable*, int);
	ElementFactory*		getElementFactory();
  virtual ISocket*		getSocket();
	IGame*				getGame() const;
  void handleMonsters();
};

#endif