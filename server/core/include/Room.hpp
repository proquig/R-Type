//
// Created by proqui_g on 12/19/16.
//

#ifndef		__R_TYPE_ROOM_HH__
# define	__R_TYPE_ROOM_HH__

# include	<algorithm>
# include	<map>
# include   "GameController.hh"
# include   "ControllerFactory.hh"
# include	"APacket.hh"
# include	"Player.hh"

# define	MAX_PLAYERS	4

class Room
{
private:
  std::vector<Player*>  _players;
  ControllerFactory     _cf;
  GameController*       _gameController;

public:
  Room();
  Room(Player* player);
  ~Room();
  GameController*       getGameController() const;
  bool 					setPlayers(std::vector<Player*> players);
  std::vector<Player*>	getPlayers() const;
  bool 					addPlayer(Player* player);
  bool 					deletePlayer(Player *player);
  void 					clearPlayers();
  bool					playerIsPresent(Player* player);
  bool					socketIsPresent(struct sockaddr* sock);
  //struct sockaddr*		getSockFromPlayer(Player* player);
  Player*				getPlayerFromSock(struct sockaddr* sock);
//  void 					sendNotificationFromPlayer(Player* player);
//  void 					sendNotificationFromSock(struct sockaddr* sock);
  bool					isFull();
  //void					sendNotification(ISocket *sock, const std::string &data);
  void					sendNotification(ISocket *sock);
};


#endif
