//
// Created by proqui_g on 12/19/16.
//

#include <ISocket.hpp>
#include <GameDataPacket.hh>
#include "Room.hpp"

Room::Room()
{

}

Room::Room(Player *player, struct sockaddr* sock)
{
  this->_players.insert(std::pair<struct sockaddr*, Player*>(sock, player));
  // 800 x 600
  player->setX(this->_players.size() * 100);
  player->setY(this->_players.size() * 100);
  player->setAngle(0);
  player->setSpeed(10);
  player->setId(this->_players.size());
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
  player->setX(this->_players.size() * 100);
  player->setY(this->_players.size() * 100);
  player->setAngle(0);
  player->setSpeed(10);
  player->setId(this->_players.size());
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

struct sockaddr *Room::getSockFromPlayer(Player *player)
{
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	if (it->second == player)
	  return (it->first);
  return nullptr;
}

Player *Room::getPlayerFromSock(struct sockaddr *sock)
{
  if (this->_players.find(sock) != this->_players.end())
	return (this->_players.find(sock)->second);
  return nullptr;
}

void Room::sendNotification(ISocket *sock, const std::string& data)
{
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	sock->write(std::vector<unsigned char>(data.begin(), data.end()), it->first);
}

void Room::sendNotification(ISocket *sock)
{
  std::vector<GameElement*>	vec;
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	vec.push_back((GameElement *&&) it->second);
  GameDataPacket packet(vec);
  packet.setHeader(APacket::GAME_ELEM_INFO, APacket::ACK_DONE, MAGIC, 4, 42, 100, 12);
  std::string	str = packet.serialize();
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	sock->write(std::vector<unsigned char>(str.begin(), str.end()), it->first);
}
