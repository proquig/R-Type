#ifndef GAMEHANDLER_GAME_HH
#define GAMEHANDLER_GAME_HH

#include	<algorithm>
#include "IGame.hh"
#include "File.hh"

class Rectangle;

class Game : public IGame {

private:
	const Rectangle&			_cadre;
	std::vector<Player*>		_players;
	int							_id;
	bool						_running;
	std::vector<RType::IElement*> 		_map;
  	uint16_t					_score;

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
	virtual std::vector<RType::IElement*>&		getMap();
	virtual void						addElems(std::vector<RType::IElement*>);
	virtual void						addElem(RType::IElement*);
	virtual const Rectangle&			getCadre() const;
  	virtual bool						deleteElem(RType::IElement *element);
  	virtual bool						isPresent(RType::IElement *element);
  	virtual void 						updateScore(uint16_t score);
  	virtual uint16_t					getScore() const;
};

#endif