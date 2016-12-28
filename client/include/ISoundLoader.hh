#pragma once

#include			"ASound.hh"

class ISoundLoader
{
public:
	enum eSound
	{
		eExplode,
		eMain,
		eShoot,
		eMenu
	};

	virtual ~ISoundLoader() {};
	virtual ASound*		getSound(eSound) = 0;
	virtual bool		initSoundMap() = 0;
	virtual void		setSound(eSound, const std::string&, bool) = 0;
};