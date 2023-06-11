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
#include <WS2tcpip.h>
#include <stdio.h>
#pragma comment (lib, "Ws2_32.lib")
#else
#define CLOSE close
#define READ read
#define WRITE write
#define U_SOCKET int
#define FLAG
#define SCREEN_CLEAR system("clear")
#define CONVERT_IN 
#define CONVERT_OUT 
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>
#endif

#include "user.h"
#define DEFAULT_PORT 27666

struct NetworkServer:public User
{
#if OS_WIND_COMPATIBLE
  WSADATA wsaData_;
#endif
  int iResult_ = 0; 
  U_SOCKET listenSock_ = 0, clientSock_ = 0;
  sockaddr_in listenAddr_ {}, clientAddr_ {};
  char recvbuf_[DEFAULT_BUFLEN] {};
  NetworkServer();
  ~NetworkServer();
  auto Listen(void)->size_t;
  auto Read(void)->size_t;
  auto Write(void)->size_t;
  auto Shutdown(void)->size_t;
};