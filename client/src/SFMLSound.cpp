#include "SFMLSound.hh"

/*! \brief Constructor of SFMLSound
*/
SFMLSound::SFMLSound(const std::string&  path, sf::SoundBuffer& buff, bool loop)
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
	return (_sound);
}

/*! \brief play of SFMLSound
*/
void			SFMLSound::play()
{
	_sound->play();
}

/*! \brief pause of SFMLSound
*/
void			SFMLSound::pause()
{
	_sound->pause();
}

/*! \brief stop of SFMLSound
*/
void			SFMLSound::stop()
{
	_sound->stop();
}