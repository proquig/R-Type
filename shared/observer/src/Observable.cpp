#include <algorithm>
#include "IObserver.hpp"
#include "Observable.hpp"

void Observable::addObserver(IObserver *o)
{
  if (std::find(_collectionObserver.begin(), _collectionObserver.end(), o) == _collectionObserver.end())
    _collectionObserver.insert(_collectionObserver.begin(), o);
}

void Observable::removeObserver(IObserver *o)
{
  std::vector<IObserver*>::iterator it;

  if ((it = std::find(_collectionObserver.begin(), _collectionObserver.end(), o)) != _collectionObserver.end())
    _collectionObserver.erase(it);
}

void Observable::notify(int status)
{
  for (std::vector<IObserver*>::iterator it = _collectionObserver.begin() ; it != _collectionObserver.end() ; ++it)
    (*it)->update(this, status);
}
