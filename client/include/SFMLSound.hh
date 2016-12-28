#pragma once

#include	<SFML/Audio.hpp>
#include	"ASound.hh"

class					SFMLSound : public ASound
{
private:
	sf::Sound*				_sound = nullptr;

public:
	SFMLSound(const std::string& path, sf::SoundBuffer&, bool loop);
	~SFMLSound();
	void*				getSound();
	void				play();
	void				pause();
	void				stop();
};