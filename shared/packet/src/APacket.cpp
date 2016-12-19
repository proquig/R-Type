//
// Created by proqui_g on 12/1/16.
//

#include "APacket.hh"
#include "InputPacket.hh"
#include "GameDataPacket.hh"

/*
 *
 * TODO:
 * 	check header getOpCodePart
 *
 */

APacket::APacket()
{
  this->_type = UNDEFINED;
  this->_header._opCode = 0;
  this->_header._magic = MAGIC;
  this->_header._game_id = 0;
  this->_header._packet_id = 0;
  this->_header._size = 0;
  this->_header._timer = 0;
}

void 			APacket::setMagic(uint8_t magic)
{
  this->_header._magic = magic;
}

uint8_t 			APacket::getMagic() const
{
  return (this->_header._magic);
}

void			APacket::setType(PACKET_TYPE type)
{
  this->_type = type;
}

IPacket::PACKET_TYPE     APacket::getType() const
{
  return (this->_type);
}

void 			APacket::setGameID(uint8_t game_id)
{
  this->_header._game_id = game_id;
}

uint8_t 			APacket::getGameID() const
{
  return (this->_header._game_id);
}

void 			APacket::setPacketID(uint8_t packet_id)
{
  this->_header._packet_id = packet_id;
}

uint8_t			APacket::getPacketID() const
{
  return (this->_header._packet_id);
}

void 			APacket::setOpCode(uint8_t opCode)
{
  this->_header._opCode = opCode;
}

uint8_t 			APacket::getOpCode() const
{
  return (this->_header._opCode);
}

void APacket::setHeader(APacket::t_header &header)
{
  this->_header = header;
}

void APacket::setHeader(IPacket::PACKET_TYPE packet_type, IPacket::PACKET_STATE packet_state, uint8_t magic, uint8_t game_id, uint8_t packet_id, uint32_t size, uint32_t timer)
{
  this->_type = packet_type;
  this->_header._opCode = (packet_type << 4 | packet_state);
  this->_header._magic = magic;
  this->_header._game_id = game_id;
  this->_header._packet_id = packet_id;
  this->_header._size = size;
  this->_header._timer = timer;
}

APacket::t_header APacket::getHeader()
{
  return (this->_header);
}

std::string	APacket::serialize()
{
  this->_content.flush();
  this->_content.str("");
  *this << this->_header._magic
		<< this->_header._game_id
		<< this->_header._packet_id
  		<< this->_header._opCode
	  	<< this->_header._size
  		<< this->_header._timer;
  return (this->_content.str());
}

bool APacket::unserialize(const std::string &data)
{
  uint16_t	i = 0;

  if (!APacket::checkHeader(data))
	return (false);
  this->_header._magic = *(uint8_t *) &data[i];
  i += sizeof(_header._magic);
  this->_header._game_id = *(uint8_t *) &data[i];
  i += sizeof(_header._game_id);
  this->_header._packet_id = *(uint8_t *) &data[i];
  i += sizeof(_header._packet_id);
  this->_type = (PACKET_TYPE) APacket::getFirstOpCodePart(data);
  this->_header._opCode = *(uint8_t *) &data[i];
  i += sizeof(_header._opCode);
  this->_header._size = htonl(*(uint32_t *) &data[i]);
  i += sizeof(_header._timer);
  this->_header._timer = htonl(*(uint32_t *) &data[i]);
  return (true);
}

void APacket::setSize(uint32_t size)
{
  this->_header._size = size;
}

uint32_t APacket::getSize() const
{
  return (this->_header._size);
}

void APacket::setTimer(uint32_t timer)
{
  this->_header._timer = timer;
}

uint32_t APacket::getTimer() const
{
  return (this->_header._timer);
}

uint16_t APacket::getHeaderSize()
{
  t_header			header;
  uint16_t	size = 0;

  size += sizeof(header._magic);
  size += sizeof(header._game_id);
  size += sizeof(header._packet_id);
  size += sizeof(header._opCode);
  size += sizeof(header._size);
  size += sizeof(header._timer);
  return (size);
}

bool	APacket::checkHeader(const std::string& data)
{
  return (data.size() >= APacket::getHeaderSize()
		  && data[0] == MAGIC
		  && ((APacket::getFirstOpCodePart(data) > -1) && (APacket::getFirstOpCodePart(data) < 4))
		  && ((APacket::getSecondOpCodePart(data) > -1) && (APacket::getSecondOpCodePart(data) < 3)));
}

uint8_t APacket::getFirstOpCodePart()
{
  return ((uint8_t)((this->_header._opCode & 0xF0) >> 4));
}

uint8_t APacket::getSecondOpCodePart()
{
  return ((uint8_t)(this->_header._opCode & 0x0F));
}

uint8_t APacket::getFirstOpCodePart(const std::string &data)
{
  return ((uint8_t)((data[3] & 0xF0) >> 4));
}

uint8_t APacket::getSecondOpCodePart(const std::string &data)
{
  return ((uint8_t)(data[3] & 0x0F));
}

APacket*	APacket::create(const std::string& data)
{
  APacket*	packet = nullptr;

  if (!APacket::checkHeader(data))
	return (packet);
  if (APacket::getFirstOpCodePart(data) == APacket::INPUT_DATA)
	packet = new InputPacket();
  else if (APacket::getFirstOpCodePart(data) == APacket::GAME_DATA
		  || APacket::getFirstOpCodePart(data) == APacket::GAME_ELEM_INFO
		  || APacket::getFirstOpCodePart(data) == APacket::PLAYER_INFO)
	packet = new GameDataPacket();
  if (packet)
	packet->unserialize(data);
  return (packet);
}