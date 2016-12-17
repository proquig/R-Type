#ifndef R_TYPE_ASOCKETPOLL_HPP_
#define R_TYPE_ASOCKETPOLL_HPP_

#include "ISocketPoll.hpp"

class ASocketPoll : public ISocketPoll
{
protected:
  int _state;
public:
  ASocketPoll(ISocketPoll::State = ISocketPoll::NONE);
  virtual ~ASocketPoll() = default;
public:
  virtual int getState();
  virtual void unregister();
  virtual void waitState(State);
  virtual void unwaitState(State);
};

#endif //R_TYPE_ASOCKETPOLL_HPP_