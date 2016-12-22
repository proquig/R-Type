#ifndef ELEMENT_HH__
# define ELEMENT_HH__

# include <iostream>
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
	virtual void	move(int, int, float, int) = 0;
	virtual void	destroy() = 0;

	//////////////////////////////////////////////
	// SETTERS
	//////////////////////////////////////////////

	virtual void	setId(unsigned int) = 0;
	virtual void	setAnimation(std::string) = 0;
	virtual void	setSize(Coords *) = 0;

	//////////////////////////////////////////////
	// GETTERS
	//////////////////////////////////////////////

	virtual unsigned int	getId(void) const = 0;
	virtual Coords *		getCoords(void) const = 0;
	virtual Coords *		getSize(void) const = 0;
	virtual std::string		getAnimation(void) const = 0;
	virtual float			getAngle(void) const = 0;
	virtual int				getSpeed(void) const = 0;

};

class AElement : public IElement
{
protected:

	unsigned int	id;
	Coords			*coords;
	Coords			*size;
	ASprite			*sprite;
	std::string		animation;
	float			angle;
	int				speed;

public:

	AElement() : coords(new Coords(0, 0)), size(new Coords(0, 0)) {}

	///////////////////////////////////////////////////////////////
	// GETTERS
	///////////////////////////////////////////////////////////////

	float			getAngle(void) const { return this->angle; }
	int				getSpeed(void) const { return this->speed; }
	unsigned int	getId(void) const { return (this->id); }
	Coords *		getCoords(void) const { return (this->coords); }
	Coords *		getSize(void) const { return (this->size); }
	std::string		getAnimation(void) const { return (this->animation);}


	/////////////////////////////////////////////////////////////////
	// SETTERS
	/////////////////////////////////////////////////////////////////

	void	setId(unsigned int _id) { this->id = _id; }
	void	setAnimation(std::string _animation) { this->animation = _animation; }
	void	setSize(Coords *_size) { this->size = _size; }
};

enum ElementType {
	PLAYER,
	MONSTER,
	MISSILE,
	OBSTACLE,
	SET
};

class				ElementFactory {
public:

	static AElement *	create(unsigned int, ElementType);
};

#endif /* !ELEMENT_HH__ */