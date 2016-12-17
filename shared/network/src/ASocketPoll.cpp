#include "ASocketPoll.hpp"

ASocketPoll::ASocketPoll(ISocketPoll::State state)
    : _state(state)
{
}

int ASocketPoll::getState()
{
  return _state;
}

void ASocketPoll::unregister()
{
  _state |= ISocketPoll::CLOSE;
}

void ASocketPoll::waitState(ISocketPoll::State state)
{
  _state |= state;
}

void ASocketPoll::unwaitState(ISocketPoll::State state)
{
  _state &= ~(state);
}
