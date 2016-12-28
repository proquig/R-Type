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
		_buffers[eShoot] = (*(new sf::SoundBuffer()));
		_buffers[eMain] = (*(new sf::SoundBuffer()));
		_buffers[eMenu] = (*(new sf::SoundBuffer()));
		_soundMap[eShoot] = new SFMLSound("../../Client/assets/shoot.wav", _buffers[eShoot], false);
		_soundMap[eMenu] = new SFMLSound("../../Client/assets/menu.wav", _buffers[eMenu], true);
		_soundMap[eMain] = new SFMLSound("../../Client/assets/main.wav", _buffers[eMain], true);
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
SFMLSound*				SFMLSoundLoader::getSound(eSound s)
{
	return ((_soundMap[s]));
}

/*! \brief setSound of SFMLSoundLoader
*/
void					SFMLSoundLoader::setSound(eSound s, const std::string& path, bool loop)
{
	_soundMap[s] = new SFMLSound(path, _buffers[s], loop);
}
