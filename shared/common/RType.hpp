#ifndef R_TYPE_RTYPE_HPP_
#define R_TYPE_RTYPE_HPP_

namespace RType
{
//Default network properties for client
# define RTYPE_CLIENT_PORT_TCP 0
# define RTYPE_CLIENT_PORT_UDP 0
# define RTYPE_CLIENT_DEFAULT_TARGET_IP "10.29.126.43"
# define RTYPE_CLIENT_DEFAULT_TARGET_PORT 8181
//Default network properties for server
# define RTYPE_SERVER_PORT_TCP 5496
# define RTYPE_SERVER_PORT_UDP 5497
//Max sample input per packet
#define MAX_INPUT 10
//enum defining controls
enum Key
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


};

#endif //R_TYPE_RTYPE_HPP_