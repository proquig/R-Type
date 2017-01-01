#include <iostream>
#undef	NDEBUG
#include <assert.h>
#include "InputPacket.hh"
#include "GameDataPacket.hh"
#include "GameElement.hpp"

/*
 *
 * TODO:
 * 	- check header
 * 	- check data
 * 	- factory
 *
 */

/*
template <int> void print(int t)
{
  std::cout << "INT DETECTED" << std::endl;
}
*/
template <typename T> void print(const T& t)
{
  if (std::is_same<int, T>::value)
    std::cout << "INT DETECTED" << std::endl;
  std::cout << sizeof(t) << std::endl;
}
//*/
template <typename First, typename... Rest> void print(const First& first, const Rest&... rest)
{
  print(first);
  //if (std::is_same<uint16_t, First>::value)
  //htons((uint16_t)first);
  //std::cout << sizeof(first) << ", ";
  print(rest...);
}
//*/

int main(int ac, char **av)
{
  GameDataPacket	packet;
  GameDataPacket	packet1;
  APacket::t_header	header;
  APacket::t_header	header1;
  InputPacket		inp;
  InputPacket		inp1;

  header._opCode = 0xFF;
  header._packet_id = 42;
  header._game_id = 4;
  header._magic = 83;
  header._size = 100;
  header._timer = 12;

  //
  GameDataPacket	packet3;
  GameDataPacket	packet4;
  char 				player_ser[] = "\x42\x04\x2a\x32\x00\x00\x00\x64\x00\x00\x00\x0c\x21\x42\x84\x42\x00\x00\x00\x83\x00\x21\x00\x42\x0a\xd7\x28\x42\x12\x00\x03\x00\x00\x00\x04\x00\x01\x00\x02\xa4\x70\x45\x41\x03\x00\x04";
  packet.setHeader(APacket::GAME_ELEM_INFO, APacket::ACK_DONE, 0x42, 4, 42, 100, 12);
  GameElement		player1;
  GameElement		player2;
  player1.setX(0x21);
  player1.setY(0x42);
  player1.setSpeed(0x12);
  player1.setAngle(42.21);
  player1.setId(0x83);
  player1.setType(0x03);
  player2.setX(0x01);
  player2.setY(0x02);
  player2.setSpeed(0x03);
  player2.setAngle(12.34);
  player2.setId(0x04);
  player2.setType(0x04);

  packet3.setHeader(APacket::GAME_ELEM_INFO, APacket::ACK_DONE, 0x42, 4, 42, 100, 12);
  packet3.putGameElement(&player1);
  assert(packet3.deleteGameElement(&player1));
  assert(!packet3.deleteGameElement(&player2));
  packet3.putGameElement(&player1);
  packet3.putGameElement(&player2);
  assert(packet3.deleteGameElement(&player2));
  assert(packet3.deleteGameElement(&player1));
  assert(!packet3.deleteGameElement(&player2));
  assert(!packet3.deleteGameElement(&player1));
  packet3.putGameElement(&player1);
  packet3.putGameElement(&player2);
  packet3.setScore(0x21428442);
  //std::cout << "VECTOR SIZE = " << packet3.getGameElements().size() << std::endl;
  //std::cout << packet3.serialize();
  //return (0);

  std::string		player_ser1;
  player_ser1.append(player_ser, sizeof(player_ser) - 1);
  std::cout << packet3.serialize();
  //exit(0);
  assert(packet3.serialize() == player_ser1);
  assert(packet4.unserialize(packet3.serialize()));
  assert(packet3.serialize() == packet4.serialize());
  assert(packet4.getGameElements()[0]->getX() == 0x21);
  assert(packet4.getGameElements()[0]->getY() == 0x42);
  assert(packet4.getGameElements()[0]->getSpeed() == 0x12);
  assert(packet4.getGameElements()[0]->getAngle() == (float)42.21);
  assert(packet4.getGameElements()[0]->getId() == 0x83);
  assert(packet4.getGameElements()[0]->getType() == 0x03);

  assert(packet4.getGameElements()[1]->getX() == 0x01);
  assert(packet4.getGameElements()[1]->getY() == 0x02);
  assert(packet4.getGameElements()[1]->getSpeed() == 0x03);
  assert(packet4.getGameElements()[1]->getAngle() == (float)12.34);
  assert(packet4.getGameElements()[1]->getId() == 0x04);
  assert(packet4.getGameElements()[1]->getType() == 0x04);
  assert(packet4.getScore() == 0x21428442);

  /*float fl = 42.21;
  char*	test = (char *)&fl;
  //packet3.set(42.84);
  //std::cout << packet3.get() << std::endl;
  //packet4.unserialize(packet3.serialize());
  //std::cout << packet4.get() << std::endl;
  std::cout << test[0];
  std::cout << test[1];
  std::cout << test[2];
  std::cout << test[3];
  char flo[] = "\x0a\xd7\x28\x42";
  for (int i = 0; i < sizeof(float); ++i)
	assert(flo[i] == test[i]);
  return (0);
   */
  //

  //packet.setHeader(header);
  packet.setHeader(APacket::GAME_ELEM_INFO, APacket::ACK_DONE, 0x42, 4, 42, 100, 12);
  packet.putGameElement(&player1);
  header1 = packet.getHeader();
  std::cout << "OpCode = " << (int)header1._opCode << std::endl;
  assert(header1._opCode == 50);
  std::cout << "PacketID = " << (int)header1._packet_id << std::endl;
  assert(header1._packet_id == 42);
  std::cout << "GameID = " << (int)header1._game_id << std::endl;
  assert(header1._game_id == 4);
  std::cout << "Magic = " << (int)header1._magic << std::endl;
  assert(header1._magic == 0x42);
  std::cout << "Size = " << (int)header1._size << std::endl;
  assert(header1._size == 100);
  std::cout << "Timer = " << (int)header1._timer << std::endl;
  assert(header1._timer == 12);
  //print("", 2, "third", true, 't');
  //char toto[] = "toto";
  //packet << "Hey !" << std::string("WADUP") << 42 << (uint16_t) 42 << true;
  //print(42, (uint16_t)42, (uint32_t)32, "toto", (uint16_t)21);
  //std::cout << packet.print();
  /*
  std::cout << "OpCode = " << (int)packet.getOpCode() << std::endl;
  std::cout << "PacketID = " << (int)packet.getPacketID() << std::endl;
  std::cout << "GameID = " << (int)packet.getGameID() << std::endl;
  std::cout << "Magic = " << (int)packet.getMagic() << std::endl;
  std::cout << "Size = " << (int)packet.getSize() << std::endl;
  std::cout << "Timer = " << (int)packet.getTimer() << std::endl;
  std::cout << packet.serialize() << std::endl;
  packet1.unserialize(packet.serialize());
  std::cout << "OpCode = " << (int)packet1.getOpCode() << std::endl;
  std::cout << "PacketID = " << (int)packet1.getPacketID() << std::endl;
  std::cout << "GameID = " << (int)packet1.getGameID() << std::endl;
  std::cout << "Magic = " << (int)packet1.getMagic() << std::endl;
  std::cout << "Size = " << (int)packet1.getSize() << std::endl;
  std::cout << "Timer = " << (int)packet1.getTimer() << std::endl;
  std::cout << packet1.serialize() << std::endl;
   */
  assert(packet1.unserialize(packet.serialize()));
  assert(packet.getOpCode() == packet1.getOpCode());
  assert(packet.getPacketID() == packet1.getPacketID());
  assert(packet.getGameID() == packet1.getGameID());
  assert(packet.getMagic() == packet1.getMagic());
  assert(packet.getSize() == packet1.getSize());
  assert(packet.getTimer() == packet1.getTimer());
  assert(packet.getGameElements()[0]->getX() == packet1.getGameElements()[0]->getX());
  assert(packet.getGameElements()[0]->getY() == packet1.getGameElements()[0]->getY());
  assert(packet.getGameElements()[0]->getSpeed() == packet1.getGameElements()[0]->getSpeed());
  assert(packet.getGameElements()[0]->getAngle() == packet1.getGameElements()[0]->getAngle());
  assert(packet.getGameElements()[0]->getId() == packet1.getGameElements()[0]->getId());
  assert(packet.getGameElements()[0]->getType() == packet1.getGameElements()[0]->getType());
  assert(packet.getScore() == packet1.getScore());

  std::cout << packet.serialize() << std::endl;
  std::cout << packet1.serialize() << std::endl;
  assert(packet.serialize() == packet1.serialize());
  inp.setHeader(APacket::INPUT_DATA, APacket::ACK_DONE, 0x42, 4, 42, 100, 12);
  assert(inp.putInput(42) == 1);
  assert(inp.deleteInput(41) == 0);
  assert(inp.deleteInput(42) == 1);
  assert(inp.deleteInput(42) == 0);
  assert(inp.putInput(42) == 1);
  assert(inp.putInput(83) == 1);
  assert(inp.putInput(41) == 1);
  assert(inp.putInput(1) == 1);
  assert(inp.putInput(2) == 1);
  assert(inp.putInput(3) == 1);
  assert(inp.putInput(4) == 1);
  assert(inp.putInput(5) == 1);
  assert(inp.putInput(6) == 1);
  assert(inp.putInput(7) == 1);
  assert(inp.putInput(8) == 1);
  assert(inp.putInput(9) == 1);
  assert(inp.putInput(10) == 0);
  std::cout << inp.serialize() << std::endl;
  inp1.unserialize(inp.serialize());
  std::cout << inp1.serialize() << std::endl;
  assert(inp.serialize() == inp1.serialize());
  std::vector<uint16_t > vec = inp1.getInputs();
  for (uint8_t i = 0; i < vec.size(); ++i)
    std::cout << (int)vec[i] << std::endl;
  std::cout << (int)inp1.getSize() << std::endl;
  std::cout << (int)packet.getFirstOpCodePart() << std::endl;
  std::cout << (int)packet.getSecondOpCodePart() << std::endl;
  std::cout << (int)APacket::getFirstOpCodePart(packet.serialize()) << std::endl;
  std::cout << (int)APacket::getSecondOpCodePart(packet.serialize()) << std::endl;
  std::cout << "CHECK = " << (int)InputPacket::checkHeader(inp.serialize()) << std::endl;
  std::cout << "CHECK = " << (int)InputPacket::checkHeader(packet.serialize()) << std::endl;
  std::cout << "CHECK = " << (int)GameDataPacket::checkHeader(inp.serialize()) << std::endl;
  std::cout << "CHECK = " << (int)GameDataPacket::checkHeader(packet.serialize()) << std::endl;
  APacket*  apacket;
  apacket = APacket::create(inp.serialize());
  std::cout << (int)apacket->getFirstOpCodePart() << std::endl;
  assert(apacket->getFirstOpCodePart() == 0);
  std::cout << (int)apacket->getSecondOpCodePart() << std::endl;
  assert(apacket->getSecondOpCodePart() == 2);
  std::cout << std::endl;
  std::cout << inp.serialize() << std::endl;
  char pack[] = "\x42\x04\x2a\x02\x00\x00\x00\x64\x00\x00\x00\x0c\x00\x2a\x00\x53\x00\x29\x00\x01\x00\x02\x00\x03\x00\x04\x00\x05\x00\x06\x00\x07\x00\x08\x00\x09";
  std::string pack1;
  pack1.append(pack, sizeof(pack) - 1);
  assert(inp.serialize() == pack1);
  std::cout << "START" << std::endl;
  assert(APacket::create(pack1) != nullptr);
  pack1[3] = 0x43;
  assert(APacket::create(pack1) == nullptr);
  pack1[3] = 0x33;
  assert(APacket::create(pack1) == nullptr);
  pack1[3] = 0x32;
  assert(APacket::create(pack1) != nullptr);
  pack1[3] = 0x00;
  assert(APacket::create(pack1) != nullptr);
  pack1[3] = 0x03;
  assert(APacket::create(pack1) == nullptr);
  pack1[3] = 0x40;
  assert(APacket::create(pack1) == nullptr);

  APacket*	aPacket;
  assert(packet3.serialize() == player_ser1);
  std::cout << player_ser1 << std::endl;
  std::cout << packet3.serialize() << std::endl;
  assert(packet3.getGameElements().size() == 2);
  //std::cout << "CLEAR" << std::endl;
  //packet3.clearGameElements();
  std::cout << packet3.getGameElements().size() << std::endl;
  assert(packet3.getGameElements().size() == 2);
  std::cout << "BREAK" << packet3.getGameElements().size() << std::endl;
  std::cout << "PASS?" << std::endl;
  for (int i = 0; i < packet3.getGameElements().size(); ++i)
	std::cout << "VEC[" << i << "] = " << packet3.getGameElements()[i]->getId() << std::endl;
  assert((aPacket = APacket::create(packet3.serialize())) != nullptr);
  std::cout << "BREAK" << ((GameDataPacket*)aPacket)->getGameElements().size() << std::endl;
  for (int i = 0; i < ((GameDataPacket*)aPacket)->getGameElements().size(); ++i)
	std::cout << "VEC[" << i << "] = " << ((GameDataPacket*)aPacket)->getGameElements()[i]->getId() << std::endl;

  assert(aPacket->serialize() == packet3.serialize());
  assert(aPacket->getType() == APacket::GAME_ELEM_INFO);
  assert(((GameDataPacket*)aPacket)->getGameElements().size() == packet3.getGameElements().size());
  assert(((GameDataPacket*)aPacket)->getGameElements()[0]->getX() == packet3.getGameElements()[0]->getX());
  assert(((GameDataPacket*)aPacket)->getGameElements()[1]->getX() == packet3.getGameElements()[1]->getX());

  std::vector<uint16_t>	inputs;
  std::vector<GameElement*> gameElements;
  InputPacket			inputPacket;
  GameDataPacket		gameDataPacket;

  assert(inputPacket.unserialize(inp.serialize()));
  inputs.push_back(1);
  inputs.push_back(2);
  inputs.push_back(3);
  inputs.push_back(4);
  inputs.push_back(5);
  inputs.push_back(6);
  inputs.push_back(7);
  inputs.push_back(8);
  inputs.push_back(9);
  inputs.push_back(10);
  inputs.push_back(11);
  inputs.push_back(12);
  inputs.push_back(13);
  assert(!inputPacket.setInputs(inputs));
  inputs.pop_back();
  assert(inputPacket.setInputs(inputs));
  assert(inputs.size() == inputPacket.getInputs().size());
  for(int i = 0; i < inputs.size(); ++i)
	assert(inputs[i] == inputPacket.getInputs()[i]);

  assert(gameDataPacket.unserialize(packet3.serialize()));
  gameElements.push_back(&player2);
  gameElements.push_back(&player1);
  gameElements.push_back(&player1);
  gameElements.push_back(&player2);
  gameDataPacket.setGameElements(gameElements);
  assert(gameElements.size() == gameDataPacket.getGameElements().size());
  for (int i = 0; i < gameElements.size(); ++i)
  {
	assert(gameElements[i]->getId() == gameDataPacket.getGameElements()[i]->getId());
	assert(gameElements[i]->getX() == gameDataPacket.getGameElements()[i]->getX());
	assert(gameElements[i]->getY() == gameDataPacket.getGameElements()[i]->getY());
	assert(gameElements[i]->getAngle() == gameDataPacket.getGameElements()[i]->getAngle());
	assert(gameElements[i]->getSpeed() == gameDataPacket.getGameElements()[i]->getSpeed());
    assert(gameElements[i]->getType() == gameDataPacket.getGameElements()[i]->getType());
  }
  return 0;
}