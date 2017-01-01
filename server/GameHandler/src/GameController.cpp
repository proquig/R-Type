#include "GameController.hh"
#include "ISocket.hpp"
#include "ITimer.hpp"

GameController::GameController(IGame* game, ISocket *socket, ITimer *timer)
	: _collisionHandler(1920, 1080), _game(game), _socket(socket), _timer(timer), _monster(nullptr), _dicMonster(nullptr), _dicBildo(nullptr)
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
  if (_monster)
  	reinterpret_cast<void *(*)(Monster *)>((*_dicMonster)->at("destroy"))(_monster);
  if (_bildo)
	reinterpret_cast<void *(*)(Bildo *)>((*_dicBildo)->at("destroy"))(_bildo);
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
  std::vector<RType::IElement*>	del;

  aEntity = _collisionHandler.foundCollisions(_game->getMap(), &destructElementId);
  for (std::pair<RType::IElement*, RType::IElement*> element : aEntity)
  {
	if (std::find(del.begin(), del.end(), element.first) == del.end())
	  del.push_back(element.first);
	if (std::find(del.begin(), del.end(), element.second) == del.end())
	  del.push_back(element.second);
	if (element.first->getType() == RType::MONSTER || element.second->getType() == RType::MONSTER)
	  this->_game->updateScore(10);
  }
  for (RType::IElement* elem : del)
  {
	this->_game->deleteElem(elem);
	if (elem->getType() != RType::PLAYER)
	  delete elem;
	else
	  ((Player*)elem)->kill();
  }
}

void GameController::handleMonsters()
{
  uint16_t rand;
  rand = (uint16_t)(std::rand() % 42);
  if (!rand)
  {
	//if ((_monster = reinterpret_cast<Monster *(*)(int, int, ElementFactory*)>((*_dicMonster)->at("new"))(900, (std::rand() % 450), &this->_elemFact)) != nullptr)
	if ((_bildo = reinterpret_cast<Bildo *(*)(int, int, ElementFactory*)>((*_dicBildo)->at("new"))(750, (std::rand() % 450), &this->_elemFact)) != nullptr)
	{
	  this->_bildo->setType(RType::MONSTER);
	  this->_game->addElem(this->_bildo);
	  std::cout << "_monster spawned" << std::endl;
	}
	//if ((_monster = reinterpret_cast<Monster *(*)(int, int, ElementFactory*)>((*_dicMonster)->at("new"))(900, (std::rand() % 450), &this->_elemFact)) != nullptr)
	if ((_bildo = reinterpret_cast<Bildo *(*)(int, int, ElementFactory*)>((*_dicBildo)->at("new"))(750, (std::rand() % 450), &this->_elemFact)) != nullptr)
	{
		this->_bildo->setType(RType::MONSTER);
		this->_game->addElem(this->_bildo);
		std::cout << "_monster spawned" << std::endl;
	}
  }
  for (RType::IElement* elem : this->_game->getMap())
	if (elem->getType() == RType::MONSTER)
	  if (((int16_t)elem->getX()) < 0)
	  {
		this->_game->deleteElem(elem);
		delete elem;
	  }
	  else if (!((Monster*)elem)->move())
		this->_game->addElem(((Monster*)elem)->shot());
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

void GameController::setDicMonster(Dictionary *dic)
{
  this->_dicMonster = dic;
}

void GameController::setDicBildo(Dictionary *dic)
{
  this->_dicBildo = dic;
}
