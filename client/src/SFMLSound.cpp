#include "SFMLSound.hh"

/*! \brief Constructor of SFMLSound
*/
SFMLSound::SFMLSound(const std::string&  path, sf::SoundBuffer& buff, bool loop, bool music)
{
	if (!music)
	{
		_sound = new sf::Sound();
		if (!buff.loadFromFile(path))
		{
			throw new std::exception();
		}
		_sound->setBuffer(buff);
		_sound->setVolume(100);
		if (loop)
			_sound->setLoop(true);
	}
	else
	{
		_music = new sf::Music();
		if (!_music->openFromFile(path))
		{
			throw new std::exception();
		}
		_music->setVolume(100);
		_music->setLoop(loop);
	}
	//	_sound->play();
}

/*! \brief Destructor of SFMLSound
*/
SFMLSound::~SFMLSound()
{
	delete (_sound);
}

/*! \brief getSound of SFMLSound
* returns a void * sound
*/
void*			SFMLSound::getSound()
{
	if (_sound != nullptr)
		return (_sound);
	else
		return (_music);
}

/*! \brief play of SFMLSound
*/
void			SFMLSound::play()
{
	if (_sound != nullptr)
		_sound->play();
	else
		_music->play();
}

/*! \brief pause of SFMLSound
*/
void			SFMLSound::pause()
{
	if (_sound != nullptr)
		_sound->pause();
	else
		_music->pause();
}

/*! \brief stop of SFMLSound
*/
void			SFMLSound::stop()
{
	if (_sound != nullptr)
		_sound->stop();
	else
		_music->stop();
}