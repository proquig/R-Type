#ifndef R_TYPE_ISOCKET_HPP_
#define R_TYPE_ISOCKET_HPP_

#include <vector>
#include "IObservable.hpp"
#include "ISocketPoll.hpp"

class ISocket : public virtual IObservable
{
public:
  enum State
  {
    NONE = 0,
    READ = 1,
    CLOSE = 2
  };
public:
  virtual ~ISocket() = default;
public:
  virtual ISocketPoll *getSocketPoll() = 0;
  virtual void close() = 0;
  virtual bool isClosed() const = 0;
  virtual struct sockaddr *getSockaddr() = 0;
  virtual std::vector<unsigned char> &read(struct sockaddr **) = 0;
  virtual void write(const std::vector<unsigned char> &, struct sockaddr *) = 0;
};

#endif //R_TYPE_ISOCKET_HPP_