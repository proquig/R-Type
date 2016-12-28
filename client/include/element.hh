#ifndef ELEMENT_HH__
# define ELEMENT_HH__

# include <chrono>
# include <iostream>
# include "RType.hpp"
# include "sprite.hh"

# define PTC_Obstacle		(char)1
# define PTC_MONSTER	(char)2
# define PTC_MISSILE	(char)4
# define PTC_OBSTACLE	(char)8
# define PTC_SET		(char)16

enum GLib
{
	SFML
};

class IElement
{
public:

	virtual void	loadSprites(GLib) = 0;
	virtual void	print(void *) = 0;
	virtual void	move(int, int, float, std::chrono::milliseconds) = 0;
	virtual void	destroy() = 0;

	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	virtual void	setId(unsigned int) = 0;
	virtual void	setAnimation(std::string) = 0;
	virtual void	setSize(Coords *) = 0;
	virtual void	setType(RType::eType _type) = 0;

	//////////////////////////////////////////////
	// GETTERS
	//////////////////////////////////////////////

	virtual unsigned int				getId(void) const = 0;
	virtual Coords *					getCoords(void) const = 0;
	virtual Coords *					getSize(void) const = 0;
	virtual std::string					getAnimation(void) const = 0;
	virtual float						getAngle(void) const = 0;
	virtual std::chrono::milliseconds	getSpeed(void) const = 0;
	virtual RType::eType					getType(void) const = 0;

};

class AElement : public IElement
{
protected:

  RType::eType					type;

	unsigned int				id;
	Coords						*coords;
	Coords						*size;
	float						scale;
	ASprite						*sprite;
	std::string					animation;
	float						angle;
	std::chrono::milliseconds	speed;
	Coords						*target;
	Coords						*distance;
	int							ttl;

public:

	AElement() : coords(new Coords(0, 0)), size(new Coords(0, 0)), target(new Coords(0, 0)), distance(new Coords(0, 0)), ttl(10) {}

	void	move(int _x, int _y, float _angle, std::chrono::milliseconds _speed) {
		this->target->x = _x;
		this->target->y = _y;
		this->distance->x = (this->target->x - this->coords->x) / 5;
		this->distance->y = (this->target->y - this->coords->y) / 5;
		this->angle = _angle;
		this->speed = _speed;
	};

	void	destroy() {};

	void	live() { this->ttl -= 1; };
	void	alive() { this->ttl = 10; };

	///////////////////////////////////////////////////////////////
	// GETTERS
	///////////////////////////////////////////////////////////////

	float						getAngle(void) const { return this->angle; }
	std::chrono::milliseconds	getSpeed(void) const { return this->speed; }
	unsigned int				getId(void) const { return (this->id); }
	Coords *					getCoords(void) const { return (this->coords); }
	Coords *					getTarget(void) const { return (this->target); }
	Coords *					getDistance(void) const { return (this->distance); }
	Coords *					getSize(void) const { return (this->size); }
	std::string					getAnimation(void) const { return (this->animation);}
  RType::eType					getType(void) const { return (this->type); }
	float						getScale(void) const { return (this->scale); }
	float						getTtl(void) const { return (this->ttl); }


	/////////////////////////////////////////////////////////////////
	// SETTERS
	/////////////////////////////////////////////////////////////////

	void	setId(unsigned int _id) { this->id = _id; }
	void	setAnimation(std::string _animation) { this->animation = _animation; }
	void	setSize(Coords *_size) { this->size = _size; }
	void	setCoords(Coords *_coords) { this->coords = _coords; }
	void	setScale(float _scale) { this->scale = _scale; }
	void	setAngle(float _angle) { this->angle = _angle; }
	void	setSpeed(std::chrono::milliseconds _speed) { this->speed = _speed; }
	void	setType(RType::eType _type) { this->type = _type; }
};

class				ElementFactory {
public:

	static AElement *	create(unsigned int, RType::eType);
};

#endif /* !ELEMENT_HH__ */