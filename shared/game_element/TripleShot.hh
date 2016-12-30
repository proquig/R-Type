#ifndef			TRIPLE_SHOT_
#define			TRIPLE_SHOT_

#include		"Shot.hh"

class TripleShot : public Shot {
private:
	int			_startX;
	bool		_activated = false;

public:
	TripleShot(uint32_t idFrom, uint32_t id, uint16_t type, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	virtual ~TripleShot();
	virtual std::vector<RType::IElement*>					collideWith(RType::IElement* elem);
	virtual bool											move();
	bool													isActivated() const;
};
#endif