#ifndef ELEMENT_HH__
# define ELEMENT_HH__

# include <iostream>
# include "sprite.hh"

# define PTC_PLAYER		(char)1
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

	virtual void	update(AElement *) = 0;
	virtual void	loadSprites(GLib) = 0;
	virtual void	print(void *) = 0;
	virtual void	move(Coords *) = 0;
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

};

class AElement : public IElement
{
protected:

	unsigned int	id;
	Coords			*coords;
	Coords			*size;
	ASprite			*sprite;
	std::string		animation;

};

enum ElementType {
	PLAYER,
	MONSTER,
	MISSILE,
	OBSTACLE,
	SET
};

class ElementFactory {
public:
	static AElement *	create(ElementType, std::string, unsigned int, unsigned int, unsigned int, unsigned int);
};

#endif /* !ELEMENT_HH__ */