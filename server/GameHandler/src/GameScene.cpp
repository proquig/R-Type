#include		"GameScene.hh"
#include	<iostream>

GameScene::GameScene()
{
}

GameScene::~GameScene()
{
}

void			GameScene::updateScene()
{
}

void			GameScene::drawNewElem()
{
}

void			GameScene::deleteElem(int id)
{
}

std::vector<GameElement*> GameScene::getMap() const
{
	return _map;
}

void				GameScene::addElems(std::vector<GameElement*> elems)
{
	for (GameElement* g : elems)
	{
		_map.push_back(g);
	}
}
