#include "GameController.hh"
#include "ISocket.hpp"
#include "ITimer.hpp"

GameController::GameController(IGame* game, ISocket *socket, ITimer *timer)
    : _collisionHandler(1920, 1080), _game(game), _socket(socket), _timer(timer)
{
  if (_socket)
    _socket->addObserver(this);
  if (_timer)
    _timer->addObserver(this);
  _tick = 0;
}

GameController::~GameController()
{
  if (_socket)
    _socket->removeObserver(this);
  if (_timer)
    _timer->removeObserver(this);
}

void			GameController::setGame(IGame* game)
{
	_game = game;
}

bool			GameController::initGame(File* file)
{
	if (_game == NULL)
	return false;
}

void			GameController::startGame()
{
	if (_game != NULL)
	_game->launch();
}

void			GameController::handleCollisions()
{
	std::vector<int>			destructElementId;
	std::vector<IElement*>		aEntity;

	aEntity = _collisionHandler.foundCollisions(_game->getScene()->getMap(), &destructElementId);
	for (std::vector<IElement *>::iterator it = aEntity.begin(); it != aEntity.end(); ++it)
	{
		std::cout << "Collision on entity " << (*it)->getId() << std::endl;
		_game->getScene()->getMap().push_back((*it));
	}
	for (std::vector<int>::iterator it = destructElementId.begin(); it != destructElementId.end(); ++it)
	{
		//sendDestructElement((*it));
	}
}

void GameController::update(int timer)
{
	_tick += timer;
	if (_tick >= _delta)
	{
		_tick = 0;
		//appel tes fonctions ici :D �a devrais marcher.
		// Faire attention de bien set la variable _delta (en milisecondes entre chaque passage)
	}
}

void GameController::update(IObservable *o, int status)
{
  if (_socket && o == _socket)
  {
    if (status & ISocket::READ)
    {
    }
    if (status & ISocket::CLOSE)
    {
    }
  }
  if (_timer && o == _timer)
    update(status);
}

ElementFactory& GameController::getElementFactory()
{
	return _elemFact;
}

ISocket *GameController::getSocket()
{
  return _socket;
}

int	GameController::getDelta() const
{
	return (_delta);
}

void GameController::setDelta(int delta)
{
	_delta = delta;
}

int GameController::getTick() const
{
	return (_tick);
}