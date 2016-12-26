#ifndef R_TYPE_MESSAGE_HPP_
#define R_TYPE_MESSAGE_HPP_

#include "IMessage.hpp"

class Message : public IMessage
{
protected:
  unsigned char _delim;
  std::size_t _limit;
  std::string _msg;
  std::string _param;
public:
  Message(unsigned char delim = '\n', std::size_t limit = 4096);
  virtual ~Message();
public:
  virtual const std::string& getMsg() const;
  virtual bool setMsg(const std::string &);
  virtual const std::string& getParam() const;
  virtual bool setParam(const std::string &);
  virtual std::vector<unsigned char> serialize() const;
  virtual long unserialize(const std::vector<unsigned char>&);
protected:
  virtual bool setString(std::string &, const std::string &);
};

#endif //R_TYPE_MESSAGE_HPP_