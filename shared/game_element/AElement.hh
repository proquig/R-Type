#ifndef AELEMENT_HH_
#define AELEMENT_HH_

#include	"IElement.hh"
#include	<iostream>

class AElement : public IElement
{
private:
	uint32_t _idFrom;
	uint32_t _id;
	uint16_t _type;
	uint16_t _x;
	uint16_t _y;
	uint16_t _hp;
	uint16_t _size_x;
	uint16_t _size_y;
	float _angle;
	char _speed;

public:
	AElement();
	~AElement();

	uint32_t	getIdFrom() const;
	uint32_t	getId() const;
	uint16_t	getType() const;
	uint16_t	getX() const;
	uint16_t	getY() const;
	uint16_t	getHp() const;
	uint16_t	getSizeX() const;
	uint16_t	getSizeY() const; 
	float		getAngle() const;
	char		getSpeed() const;

	void		setIdFrom(uint32_t idFrom);
	void		setId(uint32_t id);
	void		setType(uint16_t type);
	void		setX(uint16_t x);
	void		setY(uint16_t y);	
	void		setHp(uint16_t);
	void		setSizeX(uint16_t x);
	void		setSizeY(uint16_t y);
	void		setAngle(float angle);
	void		setSpeed(char speed);

	std::vector<IElement*>		collideWith(IElement*);
};

#endif