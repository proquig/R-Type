#ifndef R_TYPE_ITIMER_HPP_
#define R_TYPE_ITIMER_HPP_

#include "IObservable.hpp"

class ITimer : public virtual IObservable
{
public:
  virtual ~ITimer() = default;
public:
  virtual void setTimer(unsigned int) = 0;
};

#endif //R_TYPE_ITIMER_HPP_