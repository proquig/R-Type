//
// Created by proqui_g on 12/1/16.
//

#ifndef		__PACKET_RTYPE_APACKET_HH__
# define	__PACKET_RTYPE_APACKET_HH__

# include	<iostream>
# include	<sstream>
# include	"IPacket.hh"

class APacket : public	IPacket
{
protected:
  PACKET_TYPE			_type;
  t_header				_header;
  std::stringstream		_content;

public:
  APacket();
  virtual 				~APacket(){}
  void 					setHeader(t_header &header);
  void 					setHeader(PACKET_TYPE packet_type, PACKET_STATE packet_state, uint8_t magic, uint8_t game_id, uint8_t packet_id, uint32_t size, uint32_t timer);
  t_header 				getHeader();
  void 					setMagic(uint8_t magic);
  uint8_t 				getMagic() const;
  void					setType(PACKET_TYPE type);
  PACKET_TYPE			getType() const;
  void 					setGameID(uint8_t game_id);
  uint8_t 				getGameID() const;
  void 					setPacketID(uint8_t packet_id);
  uint8_t				getPacketID() const;
  void 					setOpCode(uint8_t opCode);
  uint8_t 				getOpCode() const;
  void					setSize(uint32_t size);
  uint32_t 				getSize() const;
  void					setTimer(uint32_t timer);
  uint32_t 				getTimer() const;
  virtual std::string	serialize();
  static uint16_t		getHeaderSize();
  static bool			checkHeader(const std::string &data);
  //virtual bool			checkData(const std::string& data) const = 0;
  uint8_t				getFirstOpCodePart();
  uint8_t				getSecondOpCodePart();
  static uint8_t		getFirstOpCodePart(const std::string& data);
  static uint8_t		getSecondOpCodePart(const std::string& data);
  virtual bool			unserialize(const std::string& data);
  static APacket		*create(const std::string &data);

  template <typename T>
  APacket&	operator<<(const T& t)
  {
	if (std::is_same<std::string, T>::value)
	  this->_content.write(((std::string &) t).c_str(), ((std::string &) (t)).size() + 1);
	else
	  this->_content.write((char *) &t, sizeof(t));
	return (*this);
  }

  APacket&	operator<<(uint16_t value)
  {
	uint16_t 		u16;

	u16 = htons(value);
	this->_content.write((char *) &u16, sizeof(uint16_t));
	return (*this);
  }

  APacket&	operator<<(uint32_t value)
  {
	uint32_t 		u32;

	std::cout << "VALUE = " << (float)value << std::endl;
	u32 = htonl(value);
	this->_content.write((char *) &u32, sizeof(uint32_t));
	return (*this);
  }
};

#endif
