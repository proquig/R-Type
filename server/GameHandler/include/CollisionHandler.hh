#pragma once

#include													<map>
#include													<vector>
#include													<iostream>

#include													"Rectangle.hh"
#include													"Quadtree.hh"
#include													"GameElement.hpp"

class														CollisionHandler
{
private:
	std::map<GameElement*, Rectangle>						_rectangles;
	int														_sizeX;
	int														_sizeY;
	Quadtree												_quadtree;

public:
	CollisionHandler(int, int);
	CollisionHandler(const CollisionHandler& copy);
	~CollisionHandler();
	CollisionHandler&										operator=(const CollisionHandler& copy);

public:	
	std::vector<GameElement*>								foundCollisions(std::vector<GameElement*>& entitys, std::vector<int>* collisionId);
	bool													isCollision(const Rectangle a, const Rectangle b) const;
	std::vector<GameElement*>								handleCollision(int, int, std::vector<GameElement*>&, std::vector<int>* collisionId);
	void													addScore(std::vector<GameElement*>& entities, GameElement * entity);

public:
	std::map<GameElement*, Rectangle>						getRectangles() const;
	int														getSizeX() const;
	int														getSizeY() const;
	Quadtree												getQuadtree() const;
};