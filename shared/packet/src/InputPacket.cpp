//
// Created by proqui_g on 12/5/16.
//

#include "InputPacket.hh"

/*
 *
 * TODO:
 * 	update & check size
 *
 */

InputPacket::InputPacket()
{
}

InputPacket::~InputPacket()
{
}

std::string InputPacket::serialize()
{
  APacket::serialize();
  for (uint8_t i = 0; i < this->_inputs.size(); ++i)
	*this << this->_inputs[i];
  return (this->_content.str());
}

bool InputPacket::unserialize(const std::string &data)
{
  if (!InputPacket::checkData(data))
	return (false);
  APacket::unserialize(data);
  for (int i = APacket::getHeaderSize(); i < data.size(); i += sizeof(uint16_t))
	this->_inputs.push_back(htons(*((uint16_t*)&data[i])));
  return (true);
}

bool InputPacket::checkHeader(const std::string &data)
{
  return (APacket::checkHeader(data)
		  && (APacket::getFirstOpCodePart(data) == INPUT_DATA));
}

bool InputPacket::checkData(const std::string &data)
{
  return (InputPacket::checkHeader(data)
		  && (APacket::getHeaderSize() + (12 * sizeof(uint16_t))) >= data.size()
		  && !((data.size() - APacket::getHeaderSize()) % 2));
}

std::vector<uint16_t> InputPacket::getInputs() const
{
  return (this->_inputs);
}

bool InputPacket::putInput(uint16_t input)
{
  if (this->_inputs.size() >= 12)
	return (false);
  this->_inputs.push_back(input);
  return (true);
}

bool InputPacket::deleteInput(uint16_t input)
{
  std::vector<uint16_t>::iterator	it;

  if ((it = std::find(this->_inputs.begin(), this->_inputs.end(), input)) == this->_inputs.end())
	return (false);
  this->_inputs.erase(it);
  return (true);
}

void InputPacket::clearInputs()
{
  this->_inputs.clear();
}