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
  #if OS_WIND_COMPATIBLE
  closesocket(clientSocket_);
  WSACleanup();
  #endif
}

//Инициализирует сокеты. Ожидает подключение.
auto NetworkServer::Listen(void) -> size_t
{
#if OS_WIND_COMPATIBLE
  if (iResult_ != 0)
  {
    std::cout << "!!!WSAStartup завершился с ошибкой: " << iResult_;
    return 1;
  }
  //Определяет адрес сервера и порт.
  listenAddr_.sin_addr.s_addr = htonl(INADDR_ANY);
  listenAddr_.sin_family = AF_INET;
  listenAddr_.sin_port = htons(DEFAULT_PORT);
  listenSocket_ = socket(AF_INET, SOCK_STREAM, 0);
  if (listenSocket_ == INVALID_SOCKET)
  {
    std::cout << "!!!socket завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
  iResult_ = bind(listenSocket_, (SOCKADDR *) &listenAddr_, 
    sizeof(listenAddr_));
  if (iResult_ == SOCKET_ERROR)
  {
    std::cout << "!!!bind завершился с ошибкой: " << WSAGetLastError();
    closesocket(listenSocket_);
    return 1;
  }
  iResult_ = listen(listenSocket_, 0);
  if (iResult_ == SOCKET_ERROR)
  {
    std::cout << "!!!listen завершился с ошибкой: " << WSAGetLastError();
    closesocket(listenSocket_);
    return 1;
  }
  clientSocket_ = accept(listenSocket_, NULL, NULL);
  if (clientSocket_ == INVALID_SOCKET)
  {
    std::cout << "!!!accept завершился с ошибкой: " << WSAGetLastError();
    closesocket(listenSocket_);
    return 1;
  }
  closesocket(listenSocket_);
#else
  socketFD_ = socket(AF_INET, SOCK_STREAM, 0);
  if (socketFD_ == -1) 
  {
    std::cout << "Socket creation failed!" << std::endl;
    return 1;
  }
  serveraddress_.sin_addr.s_addr = htonl(INADDR_ANY);
  //Задает номер порта для связи.
  serveraddress_.sin_port = htons(DEFAULT_PORT);
  //Использует IPv4.
  serveraddress_.sin_family = AF_INET;
  //Привязывает сокет.
  bindStatus_ = bind(socketFD_, (struct sockaddr *) &serveraddress_, 
    sizeof(serveraddress_));
  if (bindStatus_ == -1) 
  {
    std::cout << "Socket binding failed!" << std::endl;
    return 1;
  }
  //Ставит сервер на прием данных.
  connectionStatus_ = listen(socketFD_, 5);
  if (connectionStatus_ == -1) 
  {
    std::cout << "Socket is unable to listen for new connections!" 
      << std::endl;
    return 1;
  }
  else 
  {
    std::cout << "Server is listening for new connection: " << std::endl;
  }
  length_ = sizeof(client_);
  connection_ = accept(socketFD_, (struct sockaddr *) &client_, &length_);
  if (connection_ == -1) 
  {
    std::cout << "Server is unable to accept the data from client!" 
      << std::endl;
    return 1;
  }
#endif
  return 0;
}

//Принимает данные.
auto NetworkServer::Recv(void)->size_t
{
#if OS_WIND_COMPATIBLE
  iResult_ = recv(clientSocket_, recvbuf_, sizeof(recvbuf_), 0);
  if (iResult_ <= 0)
  {
    std::cout << "!!!recv завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
  else
#else
  bzero(recvbuf_, DEFAULT_BUFLEN);
  read(connection_, recvbuf_, sizeof(recvbuf_));
#endif
  std::cout << "Client: " << recvbuf_ << std::endl;
  if (strcmp(recvbuf_, "exit") == 0)
  {
    std::cout << "Соединение завершено..." << std::endl;
    return 1;
  }
  memset(recvbuf_, 0, sizeof(recvbuf_));
  return 0;
}

//Отправляет данные.
auto NetworkServer::Send(void) -> size_t
{
  std::cout << "Server: ";
  std::cin >> recvbuf_;
#if OS_WIND_COMPATIBLE
  iResult_ = send(clientSocket_, recvbuf_, sizeof(recvbuf_), 0);
  if (iResult_ == SOCKET_ERROR)
  {
    std::cout << "!!!send завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
#else
  bzero(recvbuf_, DEFAULT_BUFLEN);
  write(connection_, recvbuf_, sizeof(recvbuf_));
#endif
  if (strcmp(recvbuf_, "exit") == 0)
    return 1;
  memset(recvbuf_, 0, sizeof(recvbuf_));
  return 0;
}

//Отключает сервер.
auto NetworkServer::Shutdown(void) -> size_t
{
#if OS_WIND_COMPATIBLE
  iResult_ = shutdown(clientSocket_, SD_SEND);
  if (iResult_ == SOCKET_ERROR)
  {
    std::cout << "!!!shutdown завершился с ошибкой: " << WSAGetLastError();
    return 1;
  }
#else
  close(socketFD_);
#endif
  return 0;
}
