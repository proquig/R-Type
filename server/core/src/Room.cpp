//
// Created by proqui_g on 12/19/16.
//

#include <ISocket.hpp>
#include <GameDataPacket.hh>
#include "Room.hpp"

Room::Room()
{

}

Room::Room(Player *player)
{
  this->_players.push_back(player);
  //this->_players.insert(std::pair<struct sockaddr*, Player*>(sock, player));
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

bool 					Room::setPlayers(std::vector<Player*> players)
{
  if (players.size() > MAX_PLAYERS)
	return (false);
  this->_players = players;
  return (true);
}

std::vector<Player*>	Room::getPlayers() const
{
  return (this->_players);
}

bool 					Room::addPlayer(Player* player)
{
  if (this->_players.size() == MAX_PLAYERS)
	return (false);
  //this->_players.insert(std::pair<struct sockaddr*, Player*>(sock, player));
  this->_players.push_back(player);
  player->setX(this->_players.size() * 100);
  player->setY(this->_players.size() * 100);
  player->setAngle(0);
  player->setSpeed(10);
  player->setId(this->_players.size());
  return (true);
}

bool 					Room::deletePlayer(Player *player)
{
  std::vector<Player*>::iterator it;
  if ((it = std::find(this->_players.begin(), this->_players.end(), player)) == this->_players.end())
	return (false);
  this->_players.erase(it);
  return (true);
}

bool 						Room::playerIsPresent(Player* player)
{
  return (std::find(this->_players.begin(), this->_players.end(), player)) == this->_players.end();
}

bool 						Room::socketIsPresent(struct sockaddr* sock)
{
//  return (!(this->_players.find(sock) == this->_players.end()));
  for (uint8_t i = 0; i < this->_players.size(); ++i)
	if (this->_players[i]->getAddr() == sock)
	  return (true);
  return (false);
}

void Room::clearPlayers()
{
  this->_players.clear();
}

bool Room::isFull()
{
  return (this->_players.size() == MAX_PLAYERS);
}

Player *Room::getPlayerFromSock(struct sockaddr *sock)
{
  for (uint8_t i = 0; i < this->_players.size(); ++i)
	if (this->_players[i]->getAddr() == sock)
	return (this->_players[i]);
  return nullptr;
}

/*
void Room::sendNotification(ISocket *sock, const std::string& data)
{
  for (std::map<struct sockaddr*, Player*>::iterator it = this->_players.begin(); it != this->_players.end(); ++it)
	sock->write(std::vector<unsigned char>(data.begin(), data.end()), it->first);
}
*/

void Room::sendNotification(ISocket *sock)
{
  std::vector<GameElement*>	vec;
  for (uint8_t i = 0; i < this->_players.size(); ++i)
	vec.push_back((GameElement *&&) this->_players[i]);
  GameDataPacket packet(vec);
  packet.setHeader(APacket::GAME_ELEM_INFO, APacket::ACK_DONE, MAGIC, 4, 42, 100, 12);
  std::string	str = packet.serialize();
  for (uint8_t i = 0; i < this->_players.size(); ++i)
	sock->write(std::vector<unsigned char>(str.begin(), str.end()), this->_players[i]->getAddr());
}
