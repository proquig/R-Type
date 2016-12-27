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
	_delta = BASE_TICK;
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
	Parser parser(&_elemFact);
	RType::IElement* elem;

	if (_game == NULL || file == NULL)
		return false;
	parser.setFile(file);
	while ((elem = parser.parse()) != NULL)
	{
		_game->addElem(elem);
	}
}

void			GameController::startGame()
{
	if (_game != NULL)
		_game->launch();
}

void			GameController::handleCollisions()
{
  std::vector<int>			destructElementId;
  std::vector<std::pair<RType::IElement*, RType::IElement*> >		aEntity;

  aEntity = _collisionHandler.foundCollisions(_game->getMap(), &destructElementId);
  for (std::pair<RType::IElement*,RType::IElement*> element : aEntity)
  {
	std::cout << "I PASS HERE" << std::endl;
	std::cout << (element.first == nullptr) << (element.second == nullptr) << std::endl;
	std::cout << element.first->getId() << " WITH " << element.second->getId() << std::endl;
	this->_game->deleteElem(element.first);
	this->_game->deleteElem(element.first);

	if (element.first->getType() != RType::PLAYER)
	  delete element.first;
	else
	  std::cout << "COLLISION PLAYER" << std::endl;
	if (element.second->getType() != RType::PLAYER)
	  delete element.second;
	else
	  std::cout << "COLLISION PLAYER 2" << std::endl;
  }
}

void GameController::update(int timer)
{
	_tick += timer;
	if (_tick >= _delta)
	{
		_game->display();
		handleCollisions();
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

ElementFactory* GameController::getElementFactory()
{
	return &_elemFact;
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

IGame* GameController::getGame() const
{
	return _game;
}