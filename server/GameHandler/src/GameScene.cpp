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

std::vector<IElement*> GameScene::getMap() const
{
	return _map;
}

void				GameScene::addElems(std::vector<IElement*> elems)
{
	for (IElement* g : elems)
	{
		_map.push_back(g);
	}
}

void				GameScene::addElem(IElement* elem)
{
	_map.push_back(elem);
}
