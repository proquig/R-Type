//
// Created by proqui_g on 12/19/16.
//

#ifndef		__R_TYPE_ROOM_HH__
# define	__R_TYPE_ROOM_HH__

# include	"GameElement.hpp"
# include	<algorithm>

# define	MAX_PLAYERS	4

class Room
{
private:
  std::vector<GameElement*>		_players;

public:
  Room();
  ~Room();
  bool 							setPlayers(std::vector<GameElement* > players);
  std::vector<GameElement*>		getPlayers() const;
  bool 							addPlayer(GameElement* player);
  bool 							deletePlayer(GameElement *player);
  void 							clearPlayers();
};


#endif
