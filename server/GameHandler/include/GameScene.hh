#ifndef GAMEHANDLER_GAMESCENE_HH
#define GAMEHANDLER_GAMESCENE_HH

#include 	<vector>
#include "CollisionHandler.hh"
#include "GameElement.hpp"

class GameScene
{
private:
	std::vector<IElement*> 	_map;
	Rectangle				_bounds;

public:
	GameScene(const Rectangle&);
	~GameScene();
	void						updateScene();
	void						drawNewElem();
	void						deleteElem(int);
	std::vector<IElement*>&		getMap();
	void						addElems(std::vector<IElement*>);
	void						addElem(IElement*);
};

#endif