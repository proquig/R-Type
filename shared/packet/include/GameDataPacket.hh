//
// Created by proqui_g on 12/5/16.
//

#ifndef		__R_TYPE_GAMEDATAPACKET_HH__
# define	__R_TYPE_GAMEDATAPACKET_HH__

# include	<sstream>
# include	"APacket.hh"

class GameDataPacket : public APacket
{
private:
  float				_fl;
public:
  GameDataPacket();
  ~GameDataPacket();
  std::string		serialize();
  bool				unserialize(const std::string& data);
  static bool 		checkHeader(const std::string& data);
  static bool 		checkData(const std::string& data);
  void				set(float value);
  //std::string		print();
  float get();
};

#endif
