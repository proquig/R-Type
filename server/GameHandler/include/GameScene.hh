#ifndef GAMEHANDLER_GAMESCENE_HH
#define GAMEHANDLER_GAMESCENE_HH

#include 	<vector>
#include	"GameElement.hpp"
#include	"Rectangle.hh"

class GameScene
{
private:
	std::vector<IElement*> 	_map;
	Rectangle				_bounds;

public:
	GameScene();
	~GameScene();
	void						updateScene();
	void						drawNewElem();
	void						deleteElem(int);
	std::vector<IElement*>&		getMap();
	void						addElems(std::vector<IElement*>);
	void						addElem(IElement*);
};

#endif