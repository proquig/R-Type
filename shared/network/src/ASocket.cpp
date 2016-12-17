#include "ASocket.hpp"

ASocket::ASocket()
    : _close(true)
{
}

void ASocket::close()
{
  _close = true;
}

bool ASocket::isClosed() const
{
  return _close;
}

struct sockaddr* ASocket::getSockaddr()
{
  return &_so;
}

std::vector<unsigned char> &ASocket::read(struct sockaddr **so)
{
  return _buffIn;
}

void ASocket::write(const std::vector<unsigned char> &buff, struct sockaddr *so)
{
  _buffOut.insert(_buffOut.end(), buff.begin(), buff.end());
}
