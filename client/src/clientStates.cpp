#include <cstring>
#include "clientStates.hh"
#include "GameDataPacket.hh"
#include "GameElement.hpp"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocket.hpp"
#include "ISocketFactory.hpp"
#include "IThreadPool.hh"
#include "ITimer.hpp"

ClientStates::ClientStates()
    : _init(false), _stop(false), _waiting(false), _input(0),
    _cond(nullptr), _mutex(nullptr), _pool(nullptr),
    _socketFactory(nullptr), _socket(nullptr),
	_player1(nullptr), _bullet(nullptr), _monster(nullptr)//, _player2(nullptr), _player3(nullptr), _player4(nullptr), _bullet(nullptr)
{
  memset(&_sockaddr, '0', sizeof(_sockaddr));
  _dlManager.add(0, "threadpool", "");
  _dlManager.add(0, "rtype_network", "");
}

ClientStates::~ClientStates()
{
  if (_socketFactory)
  {
    _socketFactory->stopPoller();
    reinterpret_cast<void *(*)(ISocketFactory *)>(_dic[1]->at("destroy"))(_socketFactory);
  }
  if (_pool)
  {
    _pool->stop();
    reinterpret_cast<void *(*)(IThreadPool *)>(_dic[0]->at("destroy"))(_pool);
  }
  for (Dictionary dic : _dic)
  {
    if (dic)
      delete dic;
  }
}

bool	ClientStates::run(state to)
{
	this->error = "Unknown error.";
	if (PREVIOUS == to) {
		if (this->history.size() <= 1) {
			this->error = "Client states : No previous state.";
			return (false);
		}
		this->history.pop_back();
	}
	else
		this->history.push_back(to);
	switch (to) {
	case LAUNCH: return this->launchState();
		break;
	case MENU: return this->menuState();
		break;
	case GAME: return this->gameState();
		break;
	case SCORE: return this->scoreState();
		break;
	case END: return this->endState();
		break;
	case TEST: return this->testState();
		break;
	default: return false;
		break;
	}
	return false;
}

std::string	ClientStates::getErr(void) const
{
	return this->error;
}

//////////////////////////////////////////
// States
//////////////////////////////////////////

bool	ClientStates::launchState(void)
{
	this->controller	= new GraphicalController(SFML, 800, 450, "R-type");

  controller->addObserver(this);
	this->controller->initAction();
  if (!_init && !init())
      return false;
  return this->run(MENU);
}

bool	ClientStates::menuState(void)
{
	std::cout << "Menu ..." << std::endl;

	return this->run(GAME);
}

bool		ClientStates::gameState(void)
{
  SFMLSprite*	sprite;
  Event *event = nullptr;
  IPacket *packet;
  std::vector<uint16_t>::iterator it;
  RType::eType objType;
  
  _inputQueue.resize(10, 0);
  _mutex->lock();
  _ref = _clock.now();
  while (!_stop)
  {
    _waiting = true;
    _cond->wait(_mutex, 50);
    _waiting = false;
    if (!_stop)
    {
      //INTERNAL EVENTS
      while ((event = this->controller->eventAction()) != nullptr)
      {
        if (event->type == Event::QUIT)
        {
          _stop = true;
          break;
        }
        if (event->type == Event::KEYPRESS)
          _input |= event->key;
        if (event->type == Event::KEYRELEASE)
          _input  &= ~(event->key);
        delete event;
      }
      //PACKET EMISSION
      if (std::chrono::duration_cast<std::chrono::milliseconds>(_clock.now() - _ref).count() > 100)
      {
        _inputQueue.push_back(_input);
        if (_inputQueue.size() > MAX_INPUT)
          _inputQueue.erase(_inputQueue.begin());
        InputPacket eventPacket;
        std::string serializedEvent;
        eventPacket.setHeader(
            IPacket::INPUT_DATA, IPacket::ACK_NEED,
            MAGIC, this->game_id,
            this->packet_id, 4242, 0
        );
        eventPacket.setInputs(_inputQueue);
        serializedEvent = eventPacket.serialize();
        if (_socket)
          this->_socket->write(std::vector<unsigned char>(serializedEvent.begin(), serializedEvent.end()), &_sockaddr);
        _ref = _clock.now();
      }
      //PACKET RECEPTION
      while ((packet = _paquetQueue.pop()) != nullptr)
      {
        if (packet->getType() == APacket::GAME_ELEM_INFO)
        {
          GameDataPacket *pak = (GameDataPacket *) packet;
          for (GameElement* ptr : pak->getGameElements())
          {
			if (ptr->getType() == RType::PLAYER)
			{
			  if (!this->_player1)
			  {
				std::cout << "I PASS HERE BITCH4" << std::endl;
				this->_player1 = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet42.gif");
				//this->_player1->addRessource("CYAN_DOWN", std::vector<Cut *>{new Cut(0, 0, 33, 19), new Cut(33, 0, 33, 19)});
				this->_player1->addRessource("CYAN", std::vector<Cut *>{new Cut(66, 0, 33, 19)});
				//this->_player1->addRessource("CYAN_UP", std::vector<Cut *>{new Cut(99, 0, 33, 19), new Cut(132, 0, 33, 19)});
				this->_player1->setAnimated(false);
				this->_player1->setAnimTime(500);
				this->_player1->setLoop(true);
			  }
			  sprite = this->_player1;
			}
			else if (ptr->getType() == RType::BULLET)
			{
			  std::cout << "I PASS HERE BITCH3" << std::endl;
			  if (!this->_bullet)
			  {
				this->_bullet = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet9.gif");
				this->_bullet->addRessource("DEFAULT", std::vector<Cut *>{
						new Cut(70, 72, 30, 28)
				});
				this->_bullet->setAnimated(false);
				this->_bullet->setAnimTime(500);
				this->_bullet->setLoop(true);
			  }
			  sprite = this->_bullet;
			}
			else if (ptr->getType() == RType::MONSTER)
			{
			  std::cout << "I PASS HERE BITCH1" << std::endl;
			  if (!this->_monster)
			  {
				std::cout << "I PASS HERE BITCH2" << std::endl;
				this->_monster = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet23.gif");
				this->_monster->addRessource("DEFAULT", std::vector<Cut *>{
						new Cut(0, 0, 33, 35)/*,
						new Cut(33, 0, 33, 35),
						new Cut(66, 0, 33, 35),
						new Cut(99, 0, 33, 35),
						new Cut(132, 0, 33, 35),
						new Cut(165, 0, 33, 35),
						new Cut(196, 0, 33, 35),
						new Cut(229, 0, 33, 35)*/
				});
				this->_monster->setAnimated(false);
				this->_monster->setAnimTime(500);
				this->_monster->setLoop(true);
			  }
			  sprite = this->_monster;
			}
			objType = (RType::eType) ptr->getType();
			//if (objType == RType::PLAYER || objType == RType::BULLET || objType == RType::MONSTER)
              this->controller->elementAction(
                ptr->getId(),
                objType,
                ptr->getX(),
                ptr->getY(),
                ptr->getAngle(),
                ptr->getSpeed(),
				sprite
            );
          }
          //this->controller->elementAction(0, RType::SET, 0, 0, 0, 10);
        }
        delete packet;
      }
    }
  }
  _mutex->unlock();
  return this->run(END);
}

bool	ClientStates::scoreState(void)
{
	return true;
}

bool	ClientStates::endState(void)
{
	std::cout << "Bye Bye !" << std::endl;
	return true;
}


/////////////////////////////////////////////////////////////////////////////////////////
// UNIT_TEST
/////////////////////////////////////////////////////////////////////////////////////////

bool	ClientStates::testState(void)
{
	Event			*event = NULL;
	Coords			*player = new Coords(50, 50);
	float			angle = 0;
	Coords			*windowSize = new Coords(800, 450);
	int				testTtl = 0;

	std::cout << "=================================" << std::endl;
	std::cout << "============  TEST  =============" << std::endl;
	std::cout << "=================================" << std::endl << std::endl;

	this->controller = new GraphicalController(SFML, windowSize->x, windowSize->y, "R-type - Graphical tests");
	this->controller->initAction();

	while (!event || event->type != Event::QUIT) {

		testTtl++;

		this->controller->elementAction(1, RType::PLAYER, player->x, player->y, angle, 0);
		this->controller->elementAction(2, RType::PLAYER, 100, 50, 0, 0);
		this->controller->elementAction(3, RType::PLAYER, 150, 50, 0, 0);

		this->controller->elementAction(8, RType::MONSTER, 400, 50, 0, 0);

		if (testTtl < 100)
			this->controller->elementAction(4, RType::MISSILE, 200, 50, 0, 0);

		this->controller->elementAction(5, RType::OBSTACLE, 250, 0, 0, 0);

		this->controller->elementAction(9, RType::TEXT, 100, 0, 0, 0);

		this->controller->elementAction(0, RType::SET, 0, 0, 0, 10);


		if (event = this->controller->eventAction()) {
			std::cout << "[EVENT] " << event->name << std::endl;
			switch (event->type) {
			case Event::KEYPRESS:
				switch (event->key)
				{
				case RType::UP: player->y -= Y_SPEED; angle = -90; break;
				case RType::DOWN: player->y += Y_SPEED; angle = 90; break;
				case RType::RIGHT: player->x += X_SPEED; angle = 0; break;
				case RType::LEFT: player->x -= X_SPEED; angle = 0; break;
				}
				break;
			case Event::RESIZE: windowSize = event->size; break;
			default: break;
			}
		}
#ifdef __linux__ 
		usleep(20);
#elif _WIN32
		Sleep(20);
#endif
	}
	return this->run(END);
}

bool	ClientStates::Menu(void)
{
	Event			*event = NULL;
	Coords			*player = new Coords(50, 50);
	float			angle = 0;
	Coords			*windowSize = new Coords(800, 450);

	std::cout << "=================================" << std::endl;
	std::cout << "============  Menu  =============" << std::endl;
	std::cout << "=================================" << std::endl << std::endl;

	this->controller = new GraphicalController(SFML, windowSize->x, windowSize->y, "R-type - Graphical tests");
	this->controller->initAction();

	while (!event || event->type != Event::QUIT) {

		this->controller->elementAction(9, RType::TEXT, 0, 0, 0, 0);
		this->controller->elementAction(0, RType::SET, 0, 0, 0, 10);

		if (event = this->controller->eventAction())
		{
			this->controller->addText(9, std::string(event->name));
			if (std::string(event->name) == "ENTER")
			{
				std::string ip = this->controller->getIp(9);
				
				std::cout << "  IP = " << ip << std::endl;
			}
		}
#ifdef __linux__ 
		usleep(20);
#elif _WIN32
		Sleep(20);
#endif
	}
	return this->run(END);
}


void ClientStates::update(IObservable *o, int status)
{
  if (controller && o == controller)
  {
    if (_waiting)
      _cond->signal();
  }
  if (_socket && o == _socket)
  {
    if (status & ISocket::READ)
    {
      struct sockaddr *addr;
      std::vector<unsigned char> &ref = _socket->read(&addr);
      if (ref.size() > 0)
      {
        std::string data(ref.begin(), ref.end());
        IPacket* packet;
        if ((packet = APacket::create(data)) != nullptr)
        {
          //TODO CHECK SOURCE
          _paquetQueue.push(packet);
          ref.erase(ref.begin(), ref.end());
          if (_waiting)
            _cond->signal();
        }
      }
    }
    if (status & ISocket::CLOSE)
    {
    }
  }
}

bool ClientStates::init()
{
  Dictionary dic;
  std::string error;

  if (!_dlManager.handler.loadAll(error))
  {
    std::cout << "Failed loading library module : " << error << std::endl;
    return false;
  }
  std::cout << "Library load success" << std::endl;
  if ((dic = _dlManager.handler.getDictionaryByName("threadpool")) != NULL
      && !(*_dic.insert(_dic.end(), dic))->empty()
      && (_pool = reinterpret_cast<IThreadPool *(*)(size_t)>(_dic.back()->at("instantiate"))(4)) != nullptr
      && ((_cond = _pool->createCondVar()) != nullptr)
      && ((_mutex = _pool->createMutex()) != nullptr))
    std::cout << "pool spawned" << std::endl;
  else
    return false;
  if ((dic = _dlManager.handler.getDictionaryByName("rtype_network")) != NULL
      && !(*_dic.insert(_dic.end(), dic))->empty()
      && (_socketFactory = reinterpret_cast<ISocketFactory *(*)(IThreadPool*)>(_dic.back()->at("instantiate"))(_pool)) != nullptr)
    std::cout << "_socketFactory spawned" << std::endl;
  else
    return false;
  if ((_socket = _socketFactory->createSocketUDP(this, RTYPE_CLIENT_PORT_UDP)) == nullptr)
    return false;
  if (!_socketFactory->hintSockaddr(std::string(RTYPE_CLIENT_DEFAULT_TARGET_IP), _sockaddr, RTYPE_CLIENT_DEFAULT_TARGET_PORT))
    return false;
  _init = true;
  return (true);
}
