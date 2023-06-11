#include "network_client.h"
#include <iostream>
#if !OS_WIND_COMPATIBLE
#include <memory.h>
#endif

//Инициализирует Winsock.
NetworkClient::NetworkClient()
{
#if OS_WIND_COMPATIBLE
  iResult_ = WSAStartup(MAKEWORD(2, 2), &wsaData_);
#endif
}

//Закрывает сокет подключения к серверу. Очищает WSADATA.
NetworkClient::~NetworkClient()
{
  CLOSE(connectSock_);
#if OS_WIND_COMPATIBLE
  WSACleanup();
#endif
}

//Инициализирует сокет. Подключается к серверу.
auto NetworkClient::Connect(void) -> size_t
{
#if OS_WIND_COMPATIBLE
  if (iResult_ != 0)
  {
    std::cout << "!!!WSAStartup завершился с ошибкой: " << iResult_ 
      << std::endl;
    return 1;
  }
#endif
  //Создает сокет для подключению к серверу.
  connectSock_ = socket(2, 1, 0);
  if (connectSock_ == -1)
  {
    std::cout << "!!!создание socket завершился с ошибкой!!!" << std::endl;
    return 1;
  }
  //Подключается к серверу.
  connectAddr_.sin_addr.s_addr = inet_addr("127.0.0.1");
  connectAddr_.sin_family = AF_INET;
  connectAddr_.sin_port = htons(DEFAULT_PORT);
  iResult_ = connect(connectSock_, (struct sockaddr *) &connectAddr_, 
    sizeof(connectAddr_));
  if (iResult_ == -1)
    connectSock_ = -1;
  if (connectSock_ == -1)
  {
    std::cout << "!!!невозможно подключиться к серверу!!!" << std::endl;
    return 1;
  }
  return 0;
}

//Принимает данные.
auto NetworkClient::Read(void)->size_t
{
  iResult_ = READ(connectSock_, recvbuf_, sizeof(recvbuf_) FLAG);
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
auto NetworkClient::Write(void) -> size_t
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
  iResult_ = WRITE(connectSock_, recvbuf_, sizeof(recvbuf_) FLAG);
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

//Отключает клиента.
auto NetworkClient::Shutdown(void) -> size_t
{
  iResult_ = shutdown(connectSock_, 0x01);
  if (iResult_ == -1)
  {
    std::cout << "!!!shutdown завершился с ошибкой!!!" << std::endl;
    return 1;
  }
  return 0;
}
