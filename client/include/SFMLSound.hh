#pragma once

#include	<SFML/Audio.hpp>
#include	"ASound.hh"

class					SFMLSound : public ASound
{
private :
	sf::Sound*				_sound = nullptr;
	sf::Music*				_music = nullptr;

public :
	SFMLSound(const std::string& path, sf::SoundBuffer&, bool loop, bool music);
	~SFMLSound();
	void*				getSound();
	void				play();
	void				pause();
	void				stop();
};