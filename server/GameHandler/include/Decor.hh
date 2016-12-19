#ifndef DECOR_HH_
#define DECOR_HH_

#include "GameElement.hpp"

class Decor : public GameElement
{
	public:
	Decor();
	~Decor();

	std::vector<IElement*>					collideWith(IElement*);
};

#endif