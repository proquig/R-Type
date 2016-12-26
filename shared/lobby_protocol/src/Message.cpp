#include <algorithm>
#include "Message.hpp"

Message::Message(unsigned char delim, size_t limit) : _delim(delim), _limit(limit)
{
}

Message::~Message()
{
}

const std::string &Message::getMsg() const
{
  return _msg;
}

bool Message::setMsg(const std::string &str)
{
  return setString(_msg, str);
}

const std::string &Message::getParam() const
{
  return _param;
}

bool Message::setParam(const std::string &str)
{
  return setString(_param, str);
}

std::vector<unsigned char> Message::serialize() const
{
  std::string str(_msg + char(_delim) + _param + char(_delim));
  std::vector<unsigned char> data(str.begin(), str.end());
  return data;
}

long Message::unserialize(const std::vector<unsigned char> &data)
{
  std::vector<unsigned char>::const_iterator begin, last;

  _msg.clear();
  _param.clear();
  if (data.size() < 2
      || (last = std::find(data.begin(), data.end(), _delim)) == data.end()
      || std::find(last, data.end(), _delim) == data.end())
    return -1;
  if (last - data.begin() > 0 && last - data.begin() < _limit)
    _msg.insert(_msg.end(), data.begin(), last);
  else
    return -1;
  begin = last + 1;
  last = std::find(begin, data.end(), _delim);
  if (last - begin >= 0 && last - begin < _limit)
    _param.insert(_param.end(), begin, last);
  else
    return -1;
  return _msg.size() + _param.size() + 2;
}

bool Message::setString(std::string &dest, const std::string &from)
{
  if (from.size() > _limit)
    return false;
  if (std::find(from.begin(), from.end(), _delim) != from.end())
    return false;
  dest = from;
  return true;
}
