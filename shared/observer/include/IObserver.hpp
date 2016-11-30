#ifndef RTYPE_IOBSERVER_HPP_
#define RTYPE_IOBSERVER_HPP_

class IObservable;

class IObserver
{
public:
  virtual ~IObserver() = default;
public:
  virtual void update(IObservable*) = 0;
};

#endif //RTYPE_IOBSERVER_HPP_