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
  closesocket(connectSocket_);
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
    std::cout << "!!!WSAStartup завершился с ошибкой: " << iResult_;
    return 1;
  }
#endif
  //Создает сокет для подключению к серверу.
  connectSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (connectSocket_ == INVALID_SOCKET)
  {
    std::cout << "!!!socket завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
  //Подключается к серверу.
  connectAddr_.sin_addr.s_addr = inet_addr("127.0.0.1");
  connectAddr_.sin_family = AF_INET;
  connectAddr_.sin_port = htons(DEFAULT_PORT);
  iResult_ = connect(connectSocket_, (SOCKADDR *) &connectAddr_, 
    sizeof(connectAddr_));
  if (iResult_ == SOCKET_ERROR)
    connectSocket_ = INVALID_SOCKET;
  if (connectSocket_ == INVALID_SOCKET)
  {
    std::cout << "Невозможно подключиться к серверу!!!" << std::endl;
    return 1;
  }
  return 0;
}

//Принимает данные.
auto NetworkClient::Recv(void)->size_t
{
  iResult_ = recv(connectSocket_, recvbuf_, sizeof(recvbuf_), 0);
  if (iResult_ > 0)
    std::cout << "Server: " << recvbuf_ << std::endl;
  else
  {
    std::cout << "!!!recv завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
  if (strcmp(recvbuf_, "exit") == 0)
  {
    std::cout << "Соединение завершено..." << std::endl;
    return 1;
  }
  memset(recvbuf_, 0, sizeof(recvbuf_));
  return 0;
}

//Отправляет данные.
auto NetworkClient::Send(void) -> size_t
{
  std::cout << "Client: ";
  std::cin >> recvbuf_;
  iResult_ = send(connectSocket_, recvbuf_, sizeof(recvbuf_), 0);
  if (iResult_ == SOCKET_ERROR)
  {
    std::cout << "!!!send завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
  if (strcmp(recvbuf_, "exit") == 0)
    return 1;
  memset(recvbuf_, 0, sizeof(recvbuf_));
  return 0;
}

//Отключает клиента.
auto NetworkClient::Shutdown(void) -> size_t
{
  iResult_ = shutdown(connectSocket_, SD_SEND);
  if (iResult_ == SOCKET_ERROR)
  {
    std::cout << "!!!shutdown завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
  return 0;
}
