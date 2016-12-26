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
	std::map<RType::IElement*, Rectangle>							_rectangles;
	int														_sizeX;
	int														_sizeY;
	Quadtree												_quadtree;

public:
	CollisionHandler(int, int);
	CollisionHandler(const CollisionHandler& copy);
	~CollisionHandler();
	CollisionHandler&										operator=(const CollisionHandler& copy);

public:	
	std::vector<RType::IElement*>								foundCollisions(std::vector<RType::IElement*>& entitys, std::vector<int>* collisionId);
	bool													isCollision(const Rectangle a, const Rectangle b) const;
	std::vector<RType::IElement*>								handleCollision(int, int, std::vector<RType::IElement*>&, std::vector<int>* collisionId);
	void													addScore(std::vector<RType::IElement*>& entities, RType::IElement * entity);

public:
	std::map<RType::IElement*, Rectangle>						getRectangles() const;
	int														getSizeX() const;
	int														getSizeY() const;
	Quadtree												getQuadtree() const;
};