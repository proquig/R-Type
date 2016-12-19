//
// Created by proqui_g on 12/19/16.
//

#include "Room.hpp"

Room::Room()
{

}

Room::Room(Player *player, struct sockaddr* sock)
{
  this->_players.insert(std::pair<struct sockaddr*, Player*>(sock, player));
}

Room::~Room()
{

}

bool 					Room::setPlayers(std::map<struct sockaddr*, Player*> players)
{
  if (players.size() > MAX_PLAYERS)
	return (false);
  this->_players = players;
  return (true);
}

std::map<struct sockaddr*, Player*>	Room::getPlayers() const
{
  return (this->_players);
}

bool 					Room::addPlayer(Player* player, struct sockaddr* sock)
{
  if (this->_players.size() == MAX_PLAYERS)
	return (false);
  this->_players.insert(std::pair<struct sockaddr*, Player*>(sock, player));
  return (true);
}

bool 					Room::deletePlayer(Player *player, struct sockaddr* sock)
{
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	if (it->second == player)
	{
	  this->_players.erase(it);
	  return (true);
	}
  return (false);
}

bool 						Room::playerIsPresent(Player* player)
{
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	if (it->second == player)
	  return (true);
  return (false);
}

bool 						Room::socketIsPresent(struct sockaddr* sock)
{
  return (!(this->_players.find(sock) == this->_players.end()));
}

void Room::clearPlayers()
{
  this->_players.clear();
}

bool Room::isFull()
{
  return (this->_players.size() == MAX_PLAYERS);
}
