//
// Created by proqui_g on 12/19/16.
//

#include <set>
#include "Room.hpp"
#include "ISocket.hpp"
#include "GameDataPacket.hh"

#include <typeinfo>

Room::Room(Dictionary* dicMonster, Dictionary* dicBildo)
{
  this->_gameController = this->_cf.create(new File(""));
  this->_gameController->setDicMonster(dicMonster);
  this->_gameController->setDicBildo(dicBildo);
}

Room::Room(Dictionary* dicMonster, Dictionary* dicBildo, Player *player)
{
  this->_gameController = this->_cf.create(new File(""));
  this->_gameController->setDicMonster(dicMonster);
  this->_gameController->setDicBildo(dicBildo);
  this->_players.push_back(player);
  player->setX(100);
  player->setY(this->_players.size() * 100);
  player->setSizeX(30);
  player->setSizeY(10);
  player->setAngle(0);
  player->setSpeed(10);
  player->setId(this->_players.size());
  player->setIdFrom(0);
}

Room::~Room()
{

}

GameController *Room::getGameController() const
{
  return (this->_gameController);
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
  player->setX(100);
  player->setY(this->_players.size() * 100);
  player->setSizeX(30);
  player->setSizeY(10);
  player->setAngle(0);
  player->setSpeed(10);
  player->setId(this->_players.size());
  player->setIdFrom(0);
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
  for (RType::IElement* gameElement : this->_gameController->getGame()->getMap())
    vec.push_back((GameElement *&&) gameElement);
  GameDataPacket packet(vec, this->_gameController->getGame()->getScore());
  packet.setHeader(APacket::GAME_ELEM_INFO, APacket::ACK_DONE, MAGIC, 4, 42, 100, 12);
  std::string	str = packet.serialize();
  for (uint8_t i = 0; i < this->_players.size(); ++i)
	sock->write(std::vector<unsigned char>(str.begin(), str.end()), this->_players[i]->getAddr());
}

void Room::handle()
{
  std::vector<RType::IElement*>	del;

  this->_gameController->handleMonsters();
  this->_gameController->handleCollisions();
  for (RType::IElement* elem : this->_gameController->getGame()->getMap())
  {
    if (elem->getType() == RType::BULLET)
      if (elem->getX() > 799 || ((int16_t) elem->getX()) < 0)
      {
        //room->getGameController()->getGame()->deleteElem(elem);
        //delete elem;
        del.push_back(elem);
#ifndef NDEBUG
        std::cout << "ELEM DELETED WITH ID" << elem->getId() << std::endl;
#endif
      }
	  else
	  {
		  elem->move();
		 if (typeid(elem).name() == "TripleShot" && ((TripleShot*)elem)->isActivated())
		  {
			  _gameController->getElementFactory()->createShot(elem->getIdFrom(), elem->getX(), elem->getY() + 25, elem->getSizeX(), elem->getSizeY(), elem->getDamage(), elem->getAngle(), elem->getSpeed());
			  _gameController->getElementFactory()->createShot(elem->getIdFrom(), elem->getX(), elem->getY() - 25, elem->getSizeX(), elem->getSizeY(), elem->getDamage(), elem->getAngle(), elem->getSpeed());
		  }

	  }
  }
  std::set<RType::IElement*> unique(del.begin(), del.end());
  for (RType::IElement* elem : unique)
  {
    this->_gameController->getGame()->deleteElem(elem);
    delete elem;
  }
}