#pragma once

#include				<map>
#include				<SFML/Audio.hpp>
#include				<iostream>
#include				"ISoundLoader.hh"
#include				"SFMLSound.hh"

class					SFMLSoundLoader : public ISoundLoader
{
public:
	static SFMLSoundLoader*		sLoader;

private:
	std::map<eSound, sf::SoundBuffer>	_buffers;
	std::map<eSound, SFMLSound*>		_soundMap;

public:
	SFMLSoundLoader();
	~SFMLSoundLoader();
	static SFMLSoundLoader*			getInstance();

public:
	bool					initSoundMap();
	void					setSound(eSound, const std::string& path, bool loop);
	SFMLSound*				getSound(eSound);
};