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
	_monster(nullptr)
{
  memset(&_sockaddr, '0', sizeof(_sockaddr));
  _dlManager.add(0, "threadpool", "");
  _dlManager.add(0, "rtype_network", "");
  soundLoader = new SFMLSoundLoader();
  soundLoader->initSoundMap();
}

ClientStates::~ClientStates()
{
	if (_pool)
		_pool->stop();
	if (_socketFactory)
	{
		_socketFactory->stopPoller();
		reinterpret_cast<void *(*)(ISocketFactory *)>(_dic[1]->at("destroy"))(_socketFactory);
	}
	if (_pool)
		reinterpret_cast<void *(*)(IThreadPool *)>(_dic[0]->at("destroy"))(_pool);
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
	case LAUNCH: 
		soundLoader->getSound(ASound::eMenu)->play();
		return this->launchState();
		break;
	case MENU: return this->Menu();
		break;
	case GAME: 
		soundLoader->getSound(ASound::eMenu)->stop();
		soundLoader->getSound(ASound::eMain)->play();
		return this->gameState();
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

  	this->controller	= new GraphicalController(SFML, 800, 450, "R-type");
  	this->controller->initAction();

  	controller->addObserver(this);
	//controller->setProperty(IWindow::KEY_REPEAT, false);
	return this->run(MENU);
}

bool ClientStates::init(std::string ip)
{
	if (!ip.size())
		ip = std::string(RTYPE_CLIENT_DEFAULT_TARGET_IP);
	if ((_socket = _socketFactory->createSocketUDP(this, RTYPE_CLIENT_PORT_UDP)) == nullptr)
		return false;
	if (!_socketFactory->hintSockaddr(ip, _sockaddr, RTYPE_CLIENT_DEFAULT_TARGET_PORT))
		return false;
	_init = true;
	return (true);
}

bool	ClientStates::Menu(void)
{
  Text *text;

  Event *event = NULL;
  std::string ip;

  this->loadSprites();
  this->controller->elementAction(0, RType::SET, 0, 0, 0, 10, this->_backgroud);
  text = (Text *) this->controller->elementAction(0, RType::TEXT, 0, -50, 0, 0);
  text->loadSprites(SFML);
  text->rmString();
  while (!event || event->type != Event::QUIT)
  {
	if ((event = this->controller->eventAction()))
	{
	  text->setString(std::string(event->name));
	  if (std::string(event->name) == "ENTER")
	  {
		ip = text->getString().substr(text->getString().find(" : ") + 4);
		std::cout << "[IP] " << ip << std::endl;
		if (this->controller->checkIp(ip) && init(ip))
		{
		  std::cout << "Connection to server OK" << std::endl;
		  this->controller->removeElement(text);
		  return this->run(GAME);
		}
	  }
	}
#ifdef __linux__
	usleep(20);
#elif _WIN32
	Sleep(20);
#endif
  }
}
bool	ClientStates::menuState(void)
{
	std::cout << "Menu ..." << std::endl;

	return this->run(GAME);
}

void		ClientStates::loadSprites(void)
{
  for (uint8_t i = 0; i < 4; ++i)
	this->_player[i] = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet42.gif");
  this->_player[0]->addRessource("CYAN", std::vector<Cut *>{new Cut(66, 0, 33, 19)});
  this->_player[1]->addRessource("VIOLET", std::vector<Cut *>{new Cut(66, 17, 33, 19)});
  this->_player[2]->addRessource("GREEN", std::vector<Cut *>{new Cut(66, 34, 33, 19)});
  this->_player[3]->addRessource("RED", std::vector<Cut *>{new Cut(66, 51, 33, 19)});
  for (uint8_t i = 0; i < 4; ++i)
  {
	this->_player[i]->setAnimated(false);
  	this->_player[i]->setAnimTime(500);
  	this->_player[i]->setLoop(true);
  }

  this->_bullet[0] = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet9.gif");
  this->_bullet[0]->addRessource("DEFAULT", std::vector<Cut *>{new Cut(70, 72, 30, 28)});
  this->_bullet[1] = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet43.gif");
  this->_bullet[1]->addRessource("DEFAULT", std::vector<Cut *>{new Cut(135, 0, 12, 11)});
  for (uint8_t i = 0; i < 2; ++i)
  {
	this->_bullet[i]->setAnimated(false);
	this->_bullet[i]->setAnimTime(500);
	this->_bullet[i]->setLoop(true);
  }

  this->_monster = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet23.gif");
  this->_monster->addRessource("DEFAULT", std::vector<Cut *>{
		  new Cut(0, 0, 33, 35)
  });
  this->_monster->setAnimated(false);
  this->_monster->setAnimTime(500);
  this->_monster->setLoop(true);


	this->_bildo = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet26.gif");
	this->_bildo->addRessource("DEFAULT", std::vector<Cut *>{
			new Cut(0, 0, 65, 50)
	});
	this->_bildo->setAnimated(false);
	this->_bildo->setAnimTime(500);
	this->_bildo->setLoop(true);



	this->_boss = new SFMLSprite("./../../client/media/GAME-Assets/r-typesheet38.gif");
	this->_boss->addRessource("DEFAULT", std::vector<Cut *>{
			new Cut(0, 0, 179, 146)
	});
	this->_boss->setAnimated(false);
	this->_boss->setAnimTime(500);
	this->_boss->setLoop(true);

  this->_backgroud = new SFMLSprite("./../../client/media/GAME-Assets/WASTE_LAND.png");
  this->_backgroud->addRessource("WASTE_LAND", std::vector<Cut *>{new Cut(0, 0, 1000, 300)});
  this->_backgroud->setAnimated(false);
  this->_backgroud->setAnimTime(500);
  this->_backgroud->setLoop(false);
}

bool		ClientStates::gameState(void)
{
  //ip = std::string();
  //this->init(ip);
  SFMLSprite*	sprite;
  Event *event = nullptr;
  IPacket *packet;
  std::vector<uint16_t>::iterator it;
  RType::eType objType;

  this->loadSprites();
  _inputQueue.resize(10, 0);
  _mutex->lock();
  _ref = _clock.now();
  this->_stop = false;
  //this->controller->elementAction(0, RType::SET, 0, 0, 0, 10, this->_backgroud);
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
		  if (!(_stop = this->checkEnd(pak)))
		  {
			this->controller->scoreAction(pak->getScore());
			this->controller->resetScene();
			for (GameElement *ptr : pak->getGameElements())
			{
			  if (ptr->getType() == RType::PLAYER)
				sprite = this->_player[ptr->getId() - 1];
			  else if (ptr->getType() == RType::BULLET)
				sprite = this->_bullet[ptr->getAngle() != 90];
			  else if (ptr->getType() == RType::MONSTER)
				sprite = this->_monster;
			  else if (ptr->getType() == RType::BILDO) {
				  sprite = this->_bildo;
			  }
			  else if (ptr->getType() == RType::BOSS)
				  sprite = this->_boss;
			  objType = (RType::eType) ptr->getType();
			  //if (objType == RType::PLAYER || objType == RType::BULLET || objType == RType::MONSTER)
				//std::cout << "Type:" << ptr->getType() << std::endl;
			  this->controller->elementAction(ptr->getId(), objType, ptr->getX(), ptr->getY(), ptr->getAngle(),
											  ptr->getSpeed(), sprite);
			  delete ptr;
			}
		  }
        }
        delete packet;
      }
    }
  }
  _mutex->unlock();
  return this->run(END);
}

bool 	ClientStates::checkEnd(GameDataPacket* packet)
{
  for (GameElement* elem : packet->getGameElements())
	if (elem->getType() == RType::PLAYER)
	  return (false);
  return (true);
}

bool	ClientStates::scoreState(void)
{
	Event			*event = NULL;
	AElement		*back = NULL;

	std::cout << "Je passe la END" << std::endl;
	back = this->controller->elementAction(1, RType::BACKGROUND, 0, 0, 0,
		0);
	back->loadSprites(SFML);
	while (!event || event->type != Event::QUIT) {
		//this->controller->elementAction(0, RType::BACKGROUND, 0, 0, 0, 10);
		
		if (event = this->controller->eventAction())
		{
			if (std::string(event->name) == "ENTER")
			{
			  this->controller->removeElement(back);
			  return this->run(MENU);
			}
		}
		#ifdef __linux__ 
				usleep(20);
		#elif _WIN32
				Sleep(20);
		#endif
	}
	return true;
}

bool	ClientStates::endState(void)
{
/*	std::cout << "Good Bye !" << std::endl;
	Event			*event = NULL;
	

	while (!event || event->type != Event::QUIT) {
		//this->controller->elementAction(0, RType::BACKGROUND, 0, 0, 0, 10);
		if (event = this->controller->eventAction())
		{
			if (std::string(event->name) == "ENTER")
				return this->run(MENU);
		}
#ifdef __linux__ 
		usleep(20);
#elif _WIN32
		Sleep(20);
#endif
	}
	return true;
	return true;*/
	Event			*event = NULL;
	AElement		*back = NULL;

	back = this->controller->elementAction(0, RType::BACKGROUND, 0, 0, 0,
		0);
	back->loadSprites(SFML);
	while (!event || event->type != Event::QUIT) {
		if (event = this->controller->eventAction())
		{
			if (std::string(event->name) == "ENTER")
				return this->run(MENU);
		}
		#ifdef __linux__ 
			usleep(20);
		#elif _WIN32
			Sleep(20);
		#endif
	}
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

		//this->controller->elementAction(1, RType::PLAYER, player->x, player->y, angle, 0);
		//this->controller->elementAction(2, RType::PLAYER, 100, 50, 0, 0);
		//this->controller->elementAction(3, RType::PLAYER, 150, 50, 0, 0);

		//this->controller->elementAction(8, RType::MONSTER, 400, 50, 0, 0);

		//if (testTtl < 100)
		//	this->controller->elementAction(4, RType::MISSILE, 200, 50, 0, 0);

		//this->controller->elementAction(5, RType::OBSTACLE, 250, 0, 0, 0);

		//this->controller->elementAction(9, RType::TEXT, 100, 0, 0, 0);

		this->controller->scoreAction(120);
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
			return this->run(SCORE);
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