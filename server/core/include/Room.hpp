//
// Created by proqui_g on 12/19/16.
//

#ifndef		__R_TYPE_ROOM_HH__
# define	__R_TYPE_ROOM_HH__

# include	<algorithm>
# include	<map>
# include	"APacket.hh"
# include	"Player.hh"

# define	MAX_PLAYERS	4

class Room
{
private:
  std::map<struct sockaddr*, Player*>	_players;
  //std::vector<std::pair<struct sockaddr*, Player*>>	_players;

public:
  Room();
  Room(Player* player, struct sockaddr* sock);
  ~Room();
  bool 					setPlayers(std::map<struct sockaddr*, Player*> players);
  std::map<struct sockaddr*, Player*>	getPlayers() const;
  bool 					addPlayer(Player* player, struct sockaddr* sock);
  bool 					deletePlayer(Player *player, struct sockaddr* sock);
  void 					clearPlayers();
  bool					playerIsPresent(Player* player);
  bool					socketIsPresent(struct sockaddr* sock);
  struct sockaddr*		getSockFromPlayer(Player* player);
  Player*				getPlayerFromSock(struct sockaddr* sock);
//  void 					sendNotificationFromPlayer(Player* player);
//  void 					sendNotificationFromSock(struct sockaddr* sock);
  bool					isFull();
  void					sendNotification(ISocket *sock, const std::string &data);
  void					sendNotification(ISocket *sock);
};


#endif
