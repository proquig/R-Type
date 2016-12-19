#ifndef			SHOT_HH_
#define			SHOT_HH_

#include		"GameElement.hpp"

class Shot : public GameElement
{
	public:
	Shot();
	std::vector<IElement*>					collideWith(IElement* elem);

};

#endif