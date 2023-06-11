#include "network_server.h"
#include <iostream>
#if !OS_WIND_COMPATIBLE
#include <memory.h>
#endif

//Инициализирует Winsock.
NetworkServer::NetworkServer()
{
#if OS_WIND_COMPATIBLE
  iResult_ = WSAStartup(MAKEWORD(2, 2), &wsaData_);
#endif
}

//Закрывает сокет клиента. Очищает WSADATA.
NetworkServer::~NetworkServer()
{
  CLOSE(clientSock_);
#if OS_WIND_COMPATIBLE
  WSACleanup();
#endif
}

//Инициализирует сокеты. Ожидает подключение.
auto NetworkServer::Listen(void) -> size_t
{
#if OS_WIND_COMPATIBLE
  if (iResult_ != 0)
  {
    std::cout << "!!!WSAStartup завершился с ошибкой: " << iResult_ 
      << std::endl;
    return 1;
  }
#endif
  //Определяет адрес сервера и порт.
  listenAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
  listenAddr_.sin_family = 2;
  listenAddr_.sin_port = htons(DEFAULT_PORT);
  listenSock_ = socket(2, 1, 0);
  if (listenSock_ == -1)
  {
    std::cout << "!!!создание socket завершился с ошибкой!!!" << std::endl;
    return 1;
  }
  iResult_ = bind(listenSock_, (struct sockaddr *) &listenAddr_, 
    sizeof(listenAddr_));
  if (iResult_ == (-1))
  {
    std::cout << "!!!bind завершился с ошибкой!!!" << std::endl;
    CLOSE(listenSock_);
    return 1;
  }
  iResult_ = listen(listenSock_, 5);
  if (iResult_ == (-1))
  {
    std::cout << "!!!listen завершился с ошибкой!!!" << std::endl;
    CLOSE(listenSock_);
    return 1;
  }
  clientSock_ = accept(listenSock_, 0, 0);
  if (clientSock_ == -1)
  {
    std::cout << "!!!accept завершился с ошибкой!!!" << std::endl;
    CLOSE(listenSock_);
    return 1;
  }
  CLOSE(listenSock_);
  return 0;
}

//Принимает данные.
auto NetworkServer::Read(void)->size_t
{
  iResult_ = READ(clientSock_, recvbuf_, sizeof(recvbuf_) FLAG);
  std::string str;
  if (iResult_ <= 0)
  {
    std::cout << "!!!recv завершился с ошибкой!!!" << std::endl;
    return 1;
  }
  else
  {
    str = CONVERT_OUT(std::string(recvbuf_));
    if (str == "exit")
    {
      std::cout << "Соединение завершено..." << std::endl;
      return 1;
    }
  }
  history_.push_back(str);
  std::cout << str << std::endl;
  memset(recvbuf_, 0, sizeof(recvbuf_));
  return 0;
}

//Отправляет данные.
auto NetworkServer::Write(void) -> size_t
{
  std::cout << name_ << ": ";
  std::string str;
  std::getline(std::cin, str);
  if (str != "exit")
    str = MessageConstructor(str);
  history_.push_back(str);
  str = CONVERT_IN(str);
#if OS_WIND_COMPATIBLE
  strcpy_s(recvbuf_, str.c_str());
#else
  strcpy(recvbuf_, str.c_str());
#endif
  iResult_ = WRITE(clientSock_, recvbuf_, sizeof(recvbuf_) FLAG);
  if (iResult_ <= 0)
  {
    std::cout << "!!!send завершился с ошибкой!!!";
    return 1;
  }
  memset(recvbuf_, 0, sizeof(recvbuf_));
  if (str == "exit")
    return 1;
  SCREEN_CLEAR;
  for (auto &hist : history_)
    std::cout << hist << std::endl;
  return 0;
}

//Отключает сервер.
auto NetworkServer::Shutdown(void) -> size_t
{
  iResult_ = shutdown(clientSock_, 0x01);
  if (iResult_ == -1)
  {
    std::cout << "!!!shutdown завершился с ошибкой!!!" << std::endl;
    return 1;
  }
  return 0;
}
