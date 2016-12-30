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
	std::map<ASound::eSound, sf::SoundBuffer>	_buffers;
	std::map<ASound::eSound, SFMLSound*>	_soundMap;

public:
	SFMLSoundLoader();
	~SFMLSoundLoader();
	static SFMLSoundLoader*			getInstance();

public:
	bool					initSoundMap();
	void					setSound(ASound::eSound, const std::string& path, bool loop, bool music);
	 SFMLSound*				getSound(ASound::eSound);
};