//
// Created by proqui_g on 12/5/16.
//

#include "GameDataPacket.hh"
#include "GameElement.hpp"


/*
 *
 * TODO:
 * - CHECK SERIALIZATION & DESERIALIZATION GAMEELEMENT
 * - UPDATE SIZE
 * - TIMER
 * - PLAYERS
 *
 */

GameDataPacket::GameDataPacket()
{
}

GameDataPacket::GameDataPacket(std::vector<GameElement*> gameElements)
{
  this->_gameElements = gameElements;
}

GameDataPacket::~GameDataPacket()
{
}

std::string GameDataPacket::serialize()
{
  // TODO: ADD UP TO 4 PLAYER & OTHER ELEMENTS
  // TODO: ADD TIMER !!!
  APacket::serialize();
  for (RType::IElement* elem : this->_gameElements)
  	if (elem)
	  *this << elem->getId()
			<< elem->getX()
			<< elem->getY()
			<< elem->getAngle()
			<< elem->getSpeed()
			<< elem->getType();
  return (this->_content.str());
}

bool GameDataPacket::unserialize(const std::string &data)
{
  if (!(GameDataPacket::checkData(data) && APacket::unserialize(data)))
	return (false);
  this->_gameElements.clear();
  for (uint32_t i = APacket::getHeaderSize(); i < data.size(); i += GameDataPacket::getGameElementSize())
  {
	this->_gameElements.push_back(new GameElement);
	uint8_t j = 0;
	this->_gameElements.back()->setId(htonl(*(uint32_t *) &data[i + j]));
	j += sizeof(uint32_t);
	this->_gameElements.back()->setX(htons(*(uint16_t *) &data[i + j]));
	j += sizeof(uint16_t);
	this->_gameElements.back()->setY(htons(*(uint16_t *) &data[i + j]));
	j += sizeof(uint16_t);
	this->_gameElements.back()->setAngle(*(float *) &data[i + j]);
	j += sizeof(float);
	this->_gameElements.back()->setSpeed(data[i + j]);
	j += sizeof(uint8_t);
	this->_gameElements.back()->setType(htons(*(uint16_t *) &data[i + j]));
  }
  return (true);
}

bool GameDataPacket::checkHeader(const std::string &data)
{
  return (APacket::checkHeader(data)
		  && (APacket::getFirstOpCodePart(data) > 0)
		  && (APacket::getFirstOpCodePart(data) < 4));
}

bool GameDataPacket::checkData(const std::string &data)
{
  return (GameDataPacket::checkHeader(data)
		  && !((data.size() - APacket::getHeaderSize()) % GameDataPacket::getGameElementSize()));
}

void GameDataPacket::putGameElement(GameElement *gameElement)
{
  this->_gameElements.push_back(gameElement);
}

void GameDataPacket::setGameElements(std::vector<GameElement *> gameElements)
{
  this->_gameElements = gameElements;
}

std::vector<GameElement*>	GameDataPacket::getGameElements() const
{
  return (this->_gameElements);
}

uint16_t GameDataPacket::getGameElementSize()
{
  t_element		element;

  uint16_t		i = 0;
  i += sizeof(element.id);
  i += sizeof(element.x);
  i += sizeof(element.y);
  i += sizeof(element.angle);
  i += sizeof(element.speed);
  i += sizeof(element.type);
  return (i);
}

void GameDataPacket::clearGameElements()
{
  this->_gameElements.clear();
}

bool GameDataPacket::deleteGameElement(GameElement* gameElement)
{
  std::vector<GameElement*>::iterator	it;

  if ((it = std::find(this->_gameElements.begin(), this->_gameElements.end(), gameElement)) == this->_gameElements.end())
	return (false);
  this->_gameElements.erase(it);
  return (true);
}
