#include <cstring>
#include "clientStates.hh"
#include "ICondVar.hh"
#include "IMutex.hh"
#include "ISocket.hpp"
#include "ISocketFactory.hpp"
#include "IThreadPool.hh"

ClientStates::ClientStates()
    : _init(false), _stop(false), _waiting(false),
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
  Event			*event = nullptr;

  _mutex->lock();
  while (!_stop)
  {
    _waiting = true;
    _cond->wait(_mutex);
    _waiting = false;
    if (!_stop)
    {
      while ((event = this->controller->eventAction()) != nullptr)
      {
        if (event->type == Event::QUIT)
        {
          _stop = true;
          break;
        }
        InputPacket		eventPacket;
        std::string		serializedEvent;

        eventPacket.setHeader(
            IPacket::INPUT_DATA, IPacket::ACK_NEED,
            MAGIC, this->game_id,
            this->packet_id, 4242, 0
        );
        eventPacket.putInput(event->type);
        serializedEvent = eventPacket.serialize();
        if (_socket)
          this->_socket->write(std::vector<unsigned char>(serializedEvent.begin(), serializedEvent.end()), &_sockaddr);
      }
    }
  }
  _mutex->unlock();
  return true;
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
	Coords			*player = new Coords(200, 20);
	Coords			*windowSize = new Coords(800, 450);

	std::cout << "=================================" << std::endl;
	std::cout << "============  TEST  =============" << std::endl;
	std::cout << "=================================" << std::endl << std::endl;

	this->controller = new GraphicalController(SFML, windowSize->x, windowSize->y, "R-type - Graphical tests");
	this->controller->initAction();

	/*
	this->controller->elementAction(
		ElementFactory::create(
			1, SET, "WASTE_LAND",
			0, 0, windowSize->x, windowSize->y
		)
	);
	*/

	while (!event || event->type != Event::QUIT) {
		if (event = this->controller->eventAction()) {
			switch (event->type) {
				case Event::UP: player->y -= Y_SPEED; break;
				case Event::DOWN: player->y += Y_SPEED; break;
				case Event::RIGHT: player->x += X_SPEED; break;
				case Event::LEFT: player->x -= X_SPEED; break;
				case Event::RESIZE: windowSize = event->size; break;
				default: break;
			}

			/*
			if (player->x < 0)
				player->x = 0;
			if (player->x > windowSize->x)
				player->x = windowSize->x;
			if (player->y < 0)
				player->y = 0;
			if (player->y > windowSize->y)
				player->y = windowSize->y;

				*/
			this->controller->elementAction(
				ElementFactory::create(
					1, PLAYER, "CYAN_STAY",// + std::string(event->name),
					player->x, player->y, 300, 200
				)
			);

			// Required for the threads
			#ifdef __linux__ 
				sleep(20);
			#elif _WIN32
				Sleep(20);
			#endif
		}
	}
	return true;
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
