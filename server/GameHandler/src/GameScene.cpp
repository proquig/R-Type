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
	std::vector<IElement*>::iterator it = _map.begin();
	while (it != _map.end())
	{
		IElement* elem = (*it);
		if (!_bounds.isIn(*(new Rectangle(elem->getX(), elem->getY(), elem->getSizeX(), elem->getSizeY()))))
		{
			it = _map.erase(it);
		}
		else
		it++;
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
