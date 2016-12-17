//
// Created by proqui_g on 12/5/16.
//

#ifndef		__R_TYPE_INPUTPACKET_HH__
# define	__R_TYPE_INPUTPACKET_HH__

# include	<vector>
# include	<algorithm>
# include	"APacket.hh"

class InputPacket : public APacket
{
private:
  std::vector<uint16_t>	_inputs;
public:
  InputPacket();
  ~InputPacket();
  std::vector<uint16_t>	getInputs() const;
  bool 					putInput(uint16_t input);
  bool 					deleteInput(uint16_t input);
  void					clearInputs();
  std::string			serialize();
  bool					unserialize(const std::string& data);
  static bool 			checkHeader(const std::string& data);
  static bool			checkData(const std::string &data);
};

#endif
