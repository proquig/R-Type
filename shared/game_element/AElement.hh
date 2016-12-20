#ifndef AELEMENT_HH_
#define AELEMENT_HH_

#include	"IElement.hh"
#include	<iostream>


class AElement : public IElement
{
public:
	enum										eType
	{
		AI,
		BONUS,
		DECOR,
		PLAYER,
		BULLET,
		MONSTER
	};

protected:
	uint32_t _idFrom;
	uint32_t _id;
	uint16_t _type;
	uint16_t _x;
	uint16_t _y;
	uint16_t _hp;
	uint16_t _size_x;
	uint16_t _size_y;
	uint16_t _damage;
	float _angle;
	char _speed;

public:
	AElement();
	AElement(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	virtual ~AElement();

	uint32_t	getIdFrom() const;
	uint32_t	getId() const;
	uint16_t	getType() const;
	uint16_t	getX() const;
	uint16_t	getY() const;
	uint16_t	getHp() const;
	uint16_t	getSizeX() const;
	uint16_t	getSizeY() const; 
	uint16_t	getDamage() const;
	float		getAngle() const;
	char		getSpeed() const;

	void		setIdFrom(uint32_t idFrom);
	void		setId(uint32_t id);
	void		setType(uint16_t type);
	void		setX(uint16_t x);
	void		setY(uint16_t y);	
	void		setHp(uint16_t);
	void		setDamage(uint16_t);
	void		setSizeX(uint16_t x);
	void		setSizeY(uint16_t y);
	void		setAngle(float angle);
	void		setSpeed(char speed);

	virtual std::vector<IElement*>		collideWith(IElement*);
};

#endif