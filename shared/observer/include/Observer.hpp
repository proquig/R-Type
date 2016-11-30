#ifndef RTYPE_OBSERVER_HPP_
#define RTYPE_OBSERVER_HPP_

#include "IObserver.hpp"

class Observer : public virtual IObserver
{
public:
  Observer() = default;
  virtual ~Observer() = default;
public:
  virtual void update(IObservable*);
};

#endif //RTYPE_OBSERVER_HPP_