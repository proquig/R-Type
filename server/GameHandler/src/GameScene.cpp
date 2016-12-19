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
	for (IElement* elem : _map)
	{
	}
}

void			GameScene::drawNewElem()
{
}

void			GameScene::deleteElem(int id)
{
}

std::vector<IElement*>& GameScene::getMap()
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
