#pragma once

#include								<map>
#include								<list>
#include								<vector>
#include								<iostream>

#include								"Rectangle.hh"

class									Quadtree
{
private:
	int									_maxLvl;
	unsigned int						_maxObj;
	int									_level;
	std::vector<Rectangle>				_objects;
	Rectangle							_bounds;
	std::map<int, Quadtree*>			_nodes;

public:
										Quadtree(int plevel, Rectangle bounds);
										~Quadtree();

public:
	void								clear();
	void								split();
	int									getIndex(Rectangle rect);
	void								insert(Rectangle rect);
	std::vector<Rectangle>&				retrieve(std::vector<Rectangle>& ret, Rectangle rect);

public:
	int									getMaxLvl() const;
	unsigned int						getMaxObj() const;
	int									getLevel() const;
	const std::vector<Rectangle>&		getObjects() const;
	const Rectangle&					getBounds() const;
	const std::map<int, Quadtree*>&		getNodes() const;

	void								display() const;
};