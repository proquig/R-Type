//
// Created by proqui_g on 12/19/16.
//

#include "Room.hpp"

Room::Room()
{

}

Room::~Room()
{

}

bool						Room::setPlayers(GameElement *players)
{
  if (players.size > MAX_PLAYERS)
	return (false);
  this->_players = players;
  return (true);
}

std::vector<GameElement *>	Room::getPlayers() const
{
  return (this->_players);
}

bool 						Room::addPlayer(GameElement *player)
{
  if (this->_players.size() == MAX_PLAYERS)
	return (false);
  this->_players.push_back(player);
  return (true);
}

bool 						Room::deletePlayer(GameElement *player)
{
  std::vector<GameElement*>::iterator	it;

  if ((it = std::find(this->_inputs.begin(), this->_inputs.end(), player)) == this->_inputs.end())
	return (false);
  this->_inputs.erase(it);
  return (true);
}
