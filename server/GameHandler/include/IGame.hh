#ifndef GAMEHANDLER_IGAME_HH
#define GAMEHANDLER_IGAME_HH

class IGame
{
	public :
	virtual ~IGame(){};
	virtual bool launch() = 0;
	virtual bool stop() = 0;
	virtual bool pause() = 0;
	virtual bool end() = 0;
};

#endif