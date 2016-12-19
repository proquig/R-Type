//
// Created by proqui_g on 12/1/16.
//

#ifndef		__PACKET_RTYPE_IPACKET_HH__
# define	__PACKET_RTYPE_IPACKET_HH__

# if defined(WIN32) || defined(_WIN64)

#  pragma comment(lib, "Ws2_32.lib")
#  include	<Winsock2.h>

# else

#  include	<arpa/inet.h>

# endif

# define	MAGIC	0x42

class IPacket
{
public:

  typedef enum
  {
	NOT_USED		= 0,
	ACK_NEED		= 1,
	ACK_DONE		= 2
  } PACKET_STATE;

  typedef enum
  {
	UNDEFINED		= -1,
	INPUT_DATA		= 0,
	GAME_DATA		= 1,
	Obstacle_INFO		= 2,
	GAME_ELEM_INFO	= 3
  } PACKET_TYPE;

  typedef struct		s_header
  {
	uint8_t		_magic	= MAGIC;
	uint8_t		_game_id;
	uint8_t		_packet_id;
	uint8_t		_opCode;
	uint32_t	_size;
	uint32_t	_timer;
  }						t_header;

  virtual 				~IPacket(){}
  virtual void 			setHeader(t_header &header) = 0;
  virtual void 			setHeader(PACKET_TYPE packet_type, PACKET_STATE packet_state, uint8_t magic, uint8_t game_id, uint8_t packet_id, uint32_t size, uint32_t timer) = 0;
  virtual t_header 		getHeader() = 0;
  virtual void 			setMagic(uint8_t magic) = 0;
  virtual uint8_t 		getMagic() const = 0;
  virtual void			setType(PACKET_TYPE type) = 0;
  virtual PACKET_TYPE	getType() const = 0;
  virtual void 			setGameID(uint8_t game_id) = 0;
  virtual uint8_t 		getGameID() const = 0;
  virtual void 			setPacketID(uint8_t packet_id) = 0;
  virtual uint8_t		getPacketID() const = 0;
  virtual void 			setOpCode(uint8_t opCode) = 0;
  virtual uint8_t 		getOpCode() const = 0;
  virtual void			setSize(uint32_t size) = 0;
  virtual uint32_t 		getSize() const = 0;
  virtual void			setTimer(uint32_t timer) = 0;
  virtual uint32_t 		getTimer() const = 0;
  virtual std::string 	serialize() = 0;
  virtual bool			unserialize(const std::string& data) = 0;
  //virtual bool			checkData(const std::string& data) const = 0;
};

#endif
