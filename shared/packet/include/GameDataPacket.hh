//
// Created by proqui_g on 12/5/16.
//

#ifndef		__R_TYPE_GAMEDATAPACKET_HH__
# define	__R_TYPE_GAMEDATAPACKET_HH__

# include	<vector>
# include	<algorithm>
# include	"APacket.hh"

class GameElement;

class GameDataPacket : public APacket
{
private:

  typedef struct 	s_element
  {
	uint32_t 		id;
	uint16_t		x;
	uint16_t 		y;
	float			angle;
	uint8_t			speed;
	uint16_t		type;
  }					t_element;

  std::vector<GameElement*>	_gameElements;
public:
  GameDataPacket();
  GameDataPacket(std::vector<GameElement *> gameElements);
  ~GameDataPacket();
  std::string		serialize();
  bool				unserialize(const std::string& data);
  static bool 		checkHeader(const std::string& data);
  static bool 		checkData(const std::string& data);
  void				putGameElement(GameElement* gameElement);
  void 				setGameElements(std::vector<GameElement*> gameElements);
  std::vector<GameElement*>	getGameElements() const;
  static uint16_t	getGameElementSize();
  void				clearGameElements();
  bool				deleteGameElement(GameElement* gameElement);
};

#endif
