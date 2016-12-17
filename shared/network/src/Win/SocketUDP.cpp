#include "SocketUDP.hpp"

SocketUDP::SocketUDP(SocketPoller *poller, IObserver *obs, unsigned short port)
  : ASocket(), _port(port), _socketPoll(poller)
{
  SOCKET fd;

  this->addObserver(obs);
  _socketPoll.addObserver(this);
  if ((fd = WSASocket(AF_INET, SOCK_DGRAM, IPPROTO_UDP, nullptr, 0, 0)) != INVALID_SOCKET)
  {
    ((struct sockaddr_in *)&_so)->sin_family = AF_INET;
    ((struct sockaddr_in *)&_so)->sin_port = htons(port);
    ((struct sockaddr_in *)&_so)->sin_addr.s_addr = htonl(INADDR_ANY);
    if (bind(fd, &_so, sizeof(_so)) != -1)
    {
      _port = ntohs(((struct sockaddr_in *)&_so)->sin_port);
      _close = false;
      _socketPoll.setFd(fd);
      return;
    }
  }
  notify(ISocket::CLOSE);
}

SocketUDP::~SocketUDP()
{
  _socketPoll.removeObserver(this);
}

void SocketUDP::close()
{
  ASocket::close();
  _socketPoll.unregister();
  notify(ISocket::CLOSE);
}

ISocketPoll * SocketUDP::getSocketPoll()
{
  return &_socketPoll;
}

void SocketUDP::update(IObservable *o, int status)
{
  if (o == &_socketPoll)
  {
    if (status & ISocketPoll::READ)
    {
      if (_read())
        notify(ISocket::READ);
      else
        close();
    }
    if (status & ISocketPoll::WRITE && !_write())
      close();
  }
}

std::vector<unsigned char>& SocketUDP::read(sockaddr **so)
{
  std::map<struct sockaddr_storage*, std::list<std::vector<unsigned char>>>::iterator it = _listIn.begin();
  std::vector<unsigned char>& vec = _buffIn;

  while (it != _listIn.end())
  {
    if (it->second.size() != 0)
    {
      std::list<std::vector<unsigned char>>::iterator buffer = it->second.begin();
      while (buffer != it->second.end())
      {
        if (buffer->size() != 0)
        {
          if (so)
            *so = ((struct sockaddr*)it->first);
          return (*buffer);
        }
        buffer = it->second.erase(buffer);
      }
    }
    ++it;
  }
  return vec;
}

void SocketUDP::write(const std::vector<unsigned char>&buff, sockaddr *so)
{
  if (buff.size() != 0 && so)
  {
    _listOut.push_back(std::make_pair(buff, so));
    _socketPoll.waitState(ISocketPoll::WRITE);
  }
}

bool SocketUDP::_read()
{
  struct sockaddr_storage addr;
  int addrlen = sizeof(addr);
  std::vector<unsigned char>  buffer(65507);
  struct sockaddr_storage* addr_new;
  int len;

  memset(&addr, 0, sizeof(addr));
  if ((len = recvfrom(_socketPoll.getFd(), ((char*)&buffer.front()), buffer.size(), 0, (struct sockaddr*)(&addr), &addrlen)) == 0)
    return false;
  buffer.resize(static_cast<unsigned long>(len));
  if (_listIn.size() != 0)
  {
    std::map<struct sockaddr_storage*, std::list<std::vector<unsigned char>>>::iterator it = _listIn.begin();

    while (it != _listIn.end())
    {
      if (memcmp(it->first, &addr, sizeof(addr)) == 0)
      {
        it->second.push_back(buffer);
        return true;
      }
      ++it;
    }
  }
  addr_new = new struct sockaddr_storage;
  memcpy(addr_new, &addr, sizeof(addr));
  _listIn.insert(_listIn.end(), std::make_pair(addr_new, std::list<std::vector<unsigned char>>()));
  _listIn[addr_new].push_back(buffer);
  return true;
}

bool SocketUDP::_write()
{
  if (!_listOut.empty())
  {
    std::list<std::pair<std::vector<unsigned char>, struct sockaddr*>>::iterator it = _listOut.begin();
    if (sendto(_socketPoll.getFd(), ((char*)&it->first.front()), it->first.size(), 0, it->second, sizeof(struct sockaddr_storage)) == -1)
      return false;
    _listOut.pop_front();
  }
  if (_listOut.empty())
    _socketPoll.unwaitState(ISocketPoll::WRITE);
  return true;
}
