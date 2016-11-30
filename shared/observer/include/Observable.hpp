#ifndef RTYPE_OBSERVABLE_HPP_
#define RTYPE_OBSERVABLE_HPP_

#include <vector>
#include "IObservable.hpp"

class Observable : public virtual IObservable
{
protected:
  std::vector<IObserver*> _collectionObserver;
public:
  Observable() = default;
  virtual ~Observable() = default;
public:
  virtual void addObserver(IObserver*);
  virtual void removeObserver(IObserver*);
  virtual void notify();
};

#endif //RTYPE_OBSERVABLE_HPP_