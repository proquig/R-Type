#ifndef GAMEHANDLER_IGAME_HH
#define GAMEHANDLER_IGAME_HH

#include "Player.hh"

class IGame
{
	public :
	virtual ~IGame(){};
	virtual bool launch() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool end() = 0;
	virtual void addPlayer(Player*) = 0;
	virtual int isReady() const = 0;
	virtual void display() const = 0;
	virtual void						updateScene() = 0;
	virtual void						drawNewElem() = 0;
	virtual void						deleteElem(int) = 0;
	virtual std::vector<IElement*>&		getMap() = 0;
	virtual void						addElems(std::vector<IElement*>) = 0;
	virtual void						addElem(IElement*) = 0;
};

#endif