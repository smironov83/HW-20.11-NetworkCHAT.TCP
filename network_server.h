#pragma once

#if defined(_WIN32)
#define OS_WIND_COMPATIBLE true
#elif defined(_WIN64)
#define OS_WIND_COMPATIBLE true
#else 
#define	OS_WIND_COMPATIBLE false
#endif

#if OS_WIND_COMPATIBLE
#undef UNICODE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment (lib, "Ws2_32.lib")
#else
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#endif

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT 27666

struct NetworkServer
{
  #if OS_WIND_COMPATIBLE
  WSADATA wsaData_;
  int iResult_ = 0;
  SOCKET listenSocket_ = INVALID_SOCKET, clientSocket_ = INVALID_SOCKET;
  SOCKADDR_IN listenAddr_ {}, clientAddr_ {};
#else
  struct sockaddr_in serveraddress_, client_;
  socklen_t length_;
  int socketFD_ = 0, connection_ = 0, bindStatus_ = 0, connectionStatus_ = 0;
#endif
  char recvbuf_[DEFAULT_BUFLEN] {};

  NetworkServer();
  ~NetworkServer();
  auto Listen(void)->size_t;
  auto Recv(void)->size_t;
  auto Send(void)->size_t;
  auto Shutdown(void)->size_t;
};