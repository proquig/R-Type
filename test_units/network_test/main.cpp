#include <iostream>
#include <thread>
#include "ISocketFactory.hpp"
#include "DLManager.hh"
#include "IThreadPool.hh"
#include "IListener.hpp"
#include "Server.hpp"

int main(void)
{
  std::pair<Dictionary, Dictionary> dic;
  DLManager dlManager;
  std::string error;
  ISocketFactory *socketFactory = nullptr;
  IListener *listener = nullptr;
  IThreadPool *pool = nullptr;
  Server *server = nullptr;
  ISocket *socketUDP = nullptr;
  dlManager.add(0, "threadpool", "");
  dlManager.add(0, "rtype_network", "");
  if (dlManager.handler.loadAll(error))
  {
    std::cout << "Library load success" << std::endl;
    if ((dic.first = dlManager.handler.getDictionaryByName("threadpool")) != NULL
        && !dic.first->empty()
        && (pool = reinterpret_cast<IThreadPool *(*)(size_t)>(dic.first->at("instantiate"))(4)) != nullptr)
      std::cout << "Pool spawned" << std::endl;
    if (pool && (dic.second = dlManager.handler.getDictionaryByName("rtype_network")) != NULL
        && !dic.second->empty()
        && (socketFactory = reinterpret_cast<ISocketFactory *(*)(IThreadPool*)>(dic.second->at("instantiate"))(pool)) != nullptr)
      std::cout << "socketFactory spawned" << std::endl;
    if (pool && socketFactory)
    {
      if ((server = new Server(socketFactory, pool)) != nullptr)
      {
        std::cout << "Server spawned" << std::endl;
        if (server->init())
          server->run();
        std::cout << "Server run out" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
        socketFactory->stopPoller();
        delete server;
      }
      reinterpret_cast<void *(*)(ISocketFactory *)>(dic.first->at("destroy"))(socketFactory);
    }
    if (pool)
    {
      pool->stop();
      reinterpret_cast<void *(*)(IThreadPool *)>(dic.first->at("destroy"))(pool);
    }
    if (dic.first)
      delete dic.first;
    if (dic.second)
      delete dic.second;
  }
  dlManager.handler.closeList();
  return 0;
}
