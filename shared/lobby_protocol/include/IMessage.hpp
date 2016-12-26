#ifndef R_TYPE_IMESSAGE_HPP_
#define R_TYPE_IMESSAGE_HPP_

#include <string>
#include <vector>

class IMessage
{
public:
  virtual ~IMessage() = default;
public:
  virtual const std::string& getMsg() const = 0;
  virtual bool setMsg(const std::string &) = 0;
  virtual const std::string& getParam() const = 0;
  virtual bool setParam(const std::string &) = 0;
  virtual std::vector<unsigned char> serialize() const = 0;
  virtual long unserialize(const std::vector<unsigned char>&) = 0;
};

#endif //R_TYPE_IMESSAGE_HPP_