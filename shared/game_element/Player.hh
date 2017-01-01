#ifndef PLAYER_HH_
#define PLAYER_HH_

#include		"GameElement.hpp"

class Player : public GameElement
{
	private:
	bool		_alive;
  	struct 	sockaddr* _addr;
	int 	_invincible;


public:
  	Player();
  	Player(struct sockaddr* addr);
  	Player(uint32_t idFrom, uint32_t id, uint16_t x, uint16_t y, uint16_t hp, uint16_t sizex, uint16_t sizey, uint16_t damage, float angle, char speed);
	virtual ~Player();
	std::vector<RType::IElement*>					collideWith(RType::IElement* elem);
	void									kill();
	sockaddr*								getAddr();
	void									setAddr(sockaddr *addr);
  	bool									isAlive();
	int     								get_invincible() const;
	void 									stop_invincible();


};
#endif