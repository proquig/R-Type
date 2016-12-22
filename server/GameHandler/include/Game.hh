#ifndef GAMEHANDLER_GAME_HH
#define GAMEHANDLER_GAME_HH

#include "IGame.hh"
#include "File.hh"
#include "Rectangle.hh"


class Game : public IGame {

private:
	const Rectangle&			_cadre;
	std::vector<Player*>		_players;
	int							_id;
	bool						_running;
	std::vector<IElement*> 		_map;

public:
	Game(int, const Rectangle&);
	~Game();
	virtual bool launch();
	virtual bool stop();
	virtual bool pause();
	virtual bool end();
	virtual void addPlayer(Player*);
	virtual int isReady() const;
	virtual bool isRunning() const;
	virtual void display() const;
	virtual void						updateScene();
	virtual void						drawNewElem();
	virtual void						deleteElem(int);
	virtual std::vector<IElement*>&		getMap();
	virtual void						addElems(std::vector<IElement*>);
	virtual void						addElem(IElement*);
	virtual const Rectangle&			getCadre() const;
};

#endif