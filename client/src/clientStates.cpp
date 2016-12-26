#include <cstring>
#include "clientStates.hh"
#include "GameDataPacket.hh"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocket.hpp"
#include "ISocketFactory.hpp"
#include "IThreadPool.hh"
#include "ITimer.hpp"

ClientStates::ClientStates()
    : _init(false), _stop(false), _waiting(false), _input(0),
    _cond(nullptr), _mutex(nullptr), _pool(nullptr),
    _socketFactory(nullptr), _socket(nullptr)
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
  Event *event = nullptr;
  IPacket *packet;
  std::vector<uint16_t>::iterator it;

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
        if (_inputQueue.size() == 11)
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
			  GameDataPacket* pak = (GameDataPacket*)packet;
			  for (uint8_t i = 0; i < pak->getGameElements().size(); ++i)
			  {
				  this->controller->elementAction(
					  pak->getGameElements()[i]->getId(),
					  PLAYER, // ADD ELEMENT TYPE TO PROTOCOL
					  pak->getGameElements()[i]->getX(),
					  pak->getGameElements()[i]->getY(),
					  pak->getGameElements()[i]->getAngle(),
					  pak->getGameElements()[i]->getSpeed()
				  );
				  this->controller->elementAction(99999, SET, 0, 0, 0, 10); 
			  }
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

	std::cout << "=================================" << std::endl;
	std::cout << "============  TEST  =============" << std::endl;
	std::cout << "=================================" << std::endl << std::endl;

	this->controller = new GraphicalController(SFML, windowSize->x, windowSize->y, "R-type - Graphical tests");
	this->controller->initAction();

	while (!event || event->type != Event::QUIT) {

		this->controller->elementAction(1, PLAYER, player->x, player->y, angle, 0);
		this->controller->elementAction(2, PLAYER, 100, 50, 0, 0);
		this->controller->elementAction(3, PLAYER, 150, 50, 0, 0);
		this->controller->elementAction(4, MISSILE, 200, 50, 0, 0);
		this->controller->elementAction(5, OBSTACLE, 250, 0, 0, 0);

		this->controller->elementAction(99999, SET, 0, 0, 0, 10);

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
				sleep(20);
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
  if ((_socket = _socketFactory->createSocketUDP(this, RTYPE_PORT_CLIENT)) == nullptr)
    return false;
  if (!_socketFactory->hintSockaddr(std::string(RTYPE_IP_SERVER), _sockaddr, RTYPE_PORT_SERVER))
    return false;
  _init = true;
  return (true);
}
