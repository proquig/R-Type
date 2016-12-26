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

InputPacket::InputPacket(uint16_t maxSamples) : _maxSamples(maxSamples)
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
  if (!(InputPacket::checkData(data) && APacket::unserialize(data)))
	return (false);
  this->clearInputs();
  for (uint16_t i = APacket::getHeaderSize(); i < data.size(); i += sizeof(uint16_t))
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
		  && (APacket::getHeaderSize() + (MAX_INPUT * sizeof(uint16_t))) >= data.size()
		  && !((data.size() - APacket::getHeaderSize()) % InputPacket::getInputSize()));
}

bool InputPacket::setInputs(std::vector<uint16_t> inputs)
{
  if (inputs.size() > _maxSamples)
	return (false);
  this->_inputs = inputs;
  return (true);
}

std::vector<uint16_t> InputPacket::getInputs() const
{
  return (this->_inputs);
}

bool InputPacket::putInput(uint16_t input)
{
  if (this->_inputs.size() >= _maxSamples)
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

uint16_t InputPacket::getInputSize()
{
  return sizeof(uint16_t);
}
