#ifndef R_TYPE_SERVER_HPP_
#define R_TYPE_SERVER_HPP_

#include "GameController.hh"
#include "InputPacket.hh"
#include "ControllerFactory.hh"
#include "DLManager.hh"
#include "NetworkHandler.hpp"
#include "workQueue.hh"

class ICondVar;
class IMutex;
class IThreadPool;
class ISocketFactory;
class ITimer;
class Room;
class Player;

class Server : public IObserver
{
protected:
  int8_t mov[4][2] = {
          {0, -1},
          {0, 1},
          {-1, 0},
          {1, 0}
  };

  ICondVar *_cond;
  std::vector<Dictionary> _dic;
  DLManager _dlManager;
  ISocketFactory *_socketFactory;
  //ControllerFactory _controllerFactory;
  IMutex *_mutex;
  NetworkHandler _network;
  WorkQueue<std::pair<std::string, struct sockaddr*>> _packets;
  IThreadPool *_pool;
  ITimer *_timer;
  bool _stop;
  ISocket *_test;
  bool _waiting;
  uint8_t 	_loop;
// std::vector<struct sockaddr *>	_clients;
  std::vector<Room*>		_rooms;
public:
  Server(unsigned short port = 4242);
  virtual ~Server();
public:
  virtual bool game_test(unsigned short port, unsigned short time);
  virtual bool init();
  virtual bool run();
  virtual void stop(unsigned int);
  virtual void update(IObservable *, int status);
  virtual void createRoom(struct sockaddr* sock);
  virtual void addPlayer(struct sockaddr* sock);
  virtual void handleSocket(sockaddr *addr, APacket *packet);
  virtual void handleMovement(Room* room, Player* player, InputPacket* packet);
  virtual void handleCollision(Room* room, Player* player);
  virtual void loop();
};

#endif //R_TYPE_SERVER_HPP_