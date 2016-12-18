#ifndef GAMEHANDLER_GAMESCENE_HH
#define GAMEHANDLER_GAMESCENE_HH

#include 	<vector>
#include	"GameElement.hpp"

class GameScene
{
private:
	std::vector<IElement*> 	_map;
	
public:
	GameScene();
	~GameScene();
	void						updateScene();
	void						drawNewElem();
	void						deleteElem(int);
	std::vector<IElement*>		getMap() const;
	void						addElems(std::vector<IElement*>);
	void						addElem(IElement*);
};

#endif