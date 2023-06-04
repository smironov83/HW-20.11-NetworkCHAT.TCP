#pragma once
#if defined(_WIN32)
#define OS_WIND_COMPATIBLE true
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#elif defined(_WIN64)
#define OS_WIND_COMPATIBLE true
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#else 
#define	OS_WIND_COMPATIBLE false
#endif

#if OS_WIND_COMPATIBLE
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#else
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#endif

#define DEFAULT_BUFLEN 1024
#define DEFAULT_PORT 27666

struct NetworkClient
{
#if OS_WIND_COMPATIBLE
  WSADATA wsaData_;
  int iResult_ = 0;
  SOCKET connectSocket_ = INVALID_SOCKET;
  SOCKADDR_IN connectAddr_ {};
#endif
  char recvbuf_[DEFAULT_BUFLEN] {};

  NetworkClient();
  ~NetworkClient();
  auto Connect(void) -> size_t;
  auto Recv(void) -> size_t;
  auto Send(void) -> size_t;
  auto Shutdown(void) -> size_t;
};