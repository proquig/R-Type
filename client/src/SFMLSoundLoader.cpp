#include		"SFMLSoundLoader.hh"

SFMLSoundLoader*	SFMLSoundLoader::sLoader = new SFMLSoundLoader();

/*! \brief Constructor of SFMLSoundLoader
*/
SFMLSoundLoader::SFMLSoundLoader()
{
	initSoundMap();
}

/*! \brief Destructor of SFMLSoundLoader
*/
SFMLSoundLoader::~SFMLSoundLoader()
{
}

/*! \brief initSoundMap of SFMLSoundLoader
* returns a bool
*/
bool				SFMLSoundLoader::initSoundMap()
{
	try {
		_buffers[ASound::eShoot] = (*(new sf::SoundBuffer()));
		_buffers[ASound::eMain] = (*(new sf::SoundBuffer()));
		_buffers[ASound::eMenu] = (*(new sf::SoundBuffer()));
		_soundMap[ASound::eShoot] = new SFMLSound("../../client/media/sounds/shoot.wav", _buffers[ASound::eShoot], false, false);
		_soundMap[ASound::eMenu] = new SFMLSound("../../client/media/sounds/menu.wav", _buffers[ASound::eMenu], true, true);
		_soundMap[ASound::eMain] = new SFMLSound("../../client/media/sounds/main.wav", _buffers[ASound::eMain], true, true);
	}
	catch (std::exception)
	{
		std::cout << "[ERROR] : Fail to load a sound" << std::endl;
		return (false);
	}
	return (true);
}

/*! \brief getInstance of SFMLSoundLoader
*/
SFMLSoundLoader* SFMLSoundLoader::getInstance()
{
	return (sLoader);
}

/*! \brief getSound of SFMLSoundLoader
*/
SFMLSound*				SFMLSoundLoader::getSound(ASound::eSound s) 
{
	return ((_soundMap[s]));
}

/*! \brief setSound of SFMLSoundLoader
*/
void					SFMLSoundLoader::setSound(ASound::eSound s, const std::string& path, bool loop, bool music)
{
	_soundMap[s] = new SFMLSound(path, _buffers[s], loop, music);
}
