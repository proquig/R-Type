#ifndef GAMEHANDLER_CONTROLLERFACTORY_HH
#define GAMEHANDLER_CONTROLLERFACTORY_HH

class File;
class GameController;
class ISocket;
class ITimer;

class ControllerFactory {
private:
	int		_gameId;

public:
	ControllerFactory();
	~ControllerFactory();
	GameController* create(File *file, ISocket* = nullptr, ITimer* = nullptr);
};

#endif