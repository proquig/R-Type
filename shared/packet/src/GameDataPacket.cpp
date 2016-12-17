//
// Created by proqui_g on 12/5/16.
//

#include "GameDataPacket.hh"

GameDataPacket::GameDataPacket()
{
}

GameDataPacket::~GameDataPacket()
{
}

std::string GameDataPacket::serialize()
{
  APacket::serialize();
  *this << (uint32_t)this->_fl;
  return (this->_content.str());
}

bool GameDataPacket::unserialize(const std::string &data)
{
  //if (!GameDataPacket::checkData(data))
	//return (false);
  APacket::unserialize(data);
  std::cout << "I PASS HERE" << sizeof(float) << std::endl;
  this->_fl = (float)htonl(*((uint32_t*)&data[APacket::getHeaderSize()]));
  std::cout << "I END HERE" << this->_fl << std::endl;
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
  return (GameDataPacket::checkHeader(data));
}

void GameDataPacket::set(float value)
{
  this->_fl = value;
}

float GameDataPacket::get()
{
  return (this->_fl);
}

/*
std::string GameDataPacket::print()
{
  return this->_content.str();
}
*/