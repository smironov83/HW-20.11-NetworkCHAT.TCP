#pragma once

#if defined(_WIN32)
#define OS_WIND_COMPATIBLE true
#elif defined(_WIN64)
#define OS_WIND_COMPATIBLE true
#else 
#define	OS_WIND_COMPATIBLE false
#endif

#if OS_WIND_COMPATIBLE
#define WIN32_LEAN_AND_MEAN
#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define CLOSE closesocket
#define READ recv
#define WRITE send
#define U_SOCKET SOCKET
#define FLAG , 0
#define SCREEN_CLEAR system("cls")
#define CONVERT_IN ConvertCHCP1251toUTF8
#define CONVERT_OUT ConvertUTF8toCHCP1251
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdio.h>
#include <stdlib.h>
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")
#else
#define CLOSE close
#define READ read
#define WRITE write
#define U_SOCKET int
#define FLAG
#define SCREEN_CLEAR system("clear")
#define CONVERT_IN
#define CONVERT_OUT
#include <arpa/inet.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#endif

#include "user.h"
#define DEFAULT_PORT 27666

struct NetworkClient:public User
{
#if OS_WIND_COMPATIBLE
  WSADATA wsaData_;
#endif
  int iResult_ = 0;
  U_SOCKET connectSock_ = 0;
  struct sockaddr_in connectAddr_ {};
  char recvbuf_[DEFAULT_BUFLEN] {};

  NetworkClient();
  ~NetworkClient();
  auto Connect(void) -> size_t;
  auto Read(void) -> size_t;
  auto Write(void) -> size_t;
  auto Shutdown(void) -> size_t;
};