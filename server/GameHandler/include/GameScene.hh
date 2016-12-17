#ifndef GAMEHANDLER_GAMESCENE_HH
#define GAMEHANDLER_GAMESCENE_HH

#include 	<vector>
#include	"GameElement.hpp"

class GameScene
{
private:
	std::vector<GameElement> 	_map;
	
public:
	GameScene();
	~GameScene();
	void						updateScene();
	void						drawNewElem();
	void						deleteElem(int);
};

#endif