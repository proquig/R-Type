#pragma once

#include													<map>
#include													<vector>
#include													<iostream>

#include													"Rectangle.hh"
#include													"Quadtree.hh"
#include													"AElement.hh"

class														CollisionHandler
{
private:
	std::map<IElement*, Rectangle>							_rectangles;
	int														_sizeX;
	int														_sizeY;
	Quadtree												_quadtree;

public:
	CollisionHandler(int, int);
	CollisionHandler(const CollisionHandler& copy);
	~CollisionHandler();
	CollisionHandler&										operator=(const CollisionHandler& copy);

public:	
	std::vector<IElement*>								foundCollisions(std::vector<IElement*>& entitys, std::vector<int>* collisionId);
	bool													isCollision(const Rectangle a, const Rectangle b) const;
	std::vector<IElement*>								handleCollision(int, int, std::vector<IElement*>&, std::vector<int>* collisionId);
	void													addScore(std::vector<IElement*>& entities, IElement * entity);

public:
	std::map<IElement*, Rectangle>						getRectangles() const;
	int														getSizeX() const;
	int														getSizeY() const;
	Quadtree												getQuadtree() const;
};