#ifndef R_TYPE_RTYPE_HPP_
#define R_TYPE_RTYPE_HPP_

namespace RType
{
//Default network properties for client
# define RTYPE_CLIENT_PORT_TCP 0
# define RTYPE_CLIENT_PORT_UDP 0
# define RTYPE_CLIENT_DEFAULT_TARGET_IP "127.0.0.1"
# define RTYPE_CLIENT_DEFAULT_TARGET_PORT 4242
//Default network properties for server
# define RTYPE_SERVER_PORT_TCP 5496
# define RTYPE_SERVER_PORT_UDP 5497
//Max sample input per packet
#define MAX_INPUT 12
//enum defining controls
enum eKey
{
  NONE = 1 << 0,
  ENTER = 1 << 1,
  SPACE = 1 << 2,
  UP = 1 << 3,
  DOWN = 1 << 4,
  LEFT = 1 << 5,
  RIGHT = 1 << 6,
};
//enum defining element type
enum eType
{
    //None
            EMPTY = 1 << 0,
    //Player
            PLAYER = 1 << 1,
    //Bullet/missile
            BULLET = 1 << 2,
    MISSILE = 1 << 2,
    //Monster
            MONSTER = 1 << 3,
    BOSS = 1 << 4,
    C3PO = 1 << 5,
    BILDO = 1 << 6,
    //Decor
            DECOR = 1 << 7,
    SET = 1 << 8,
    //Obstacle
            OBSTACLE = 1 << 9,
    //Bonus
    //UI
            TEXT = 1 << 10,
    SCORE = 1 << 11,
    BACKGROUND = 1 << 12
};

};

#endif //R_TYPE_RTYPE_HPP_
