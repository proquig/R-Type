#pragma once

#include			"ASound.hh"

class ISoundLoader
{
public:
	virtual ~ISoundLoader() {};
	virtual ASound*		getSound(ASound::eSound) = 0;
	virtual bool		initSoundMap() = 0;
	virtual void		setSound(ASound::eSound, const std::string&, bool, bool) = 0;
};