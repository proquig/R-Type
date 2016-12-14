#ifndef RTYPE_IOBSERVABLE_HPP_
#define RTYPE_IOBSERVABLE_HPP_

class IObserver;

class IObservable
{
public:
  virtual ~IObservable() = default;
public:
  virtual void addObserver(IObserver*) = 0;
  virtual void removeObserver(IObserver*) = 0;
  virtual void notify(int) = 0;
};

#endif //RTYPE_IOBSERVABLE_HPP_