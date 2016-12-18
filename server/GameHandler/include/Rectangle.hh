#pragma once

#include			<iostream>

class				Rectangle
{
private:
	int				_sizeX;
	int				_sizeY;
	int				_posX;
	int				_posY;
	int				_id;

public:
	Rectangle(int = 0, int = 0, int = 0, int = 0, int = 0);
	~Rectangle();
	Rectangle(const Rectangle&);

public:
	int				getSizeX() const;
	int				getSizeY() const;
	int				getPosX() const;
	int				getPosY() const;
	int				getId() const;
	void			display() const;
};
