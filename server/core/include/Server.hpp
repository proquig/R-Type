#ifndef R_TYPE_SERVER_HPP_
#define R_TYPE_SERVER_HPP_

#include "NetworkHandler.hpp"

class Server
{
protected:
  NetworkHandler _network;
public:
  Server();
  virtual ~Server();
};

#endif //R_TYPE_SERVER_HPP_