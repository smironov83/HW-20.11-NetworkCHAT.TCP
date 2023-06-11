#include <iostream>
#include "network_server.h"

#if OS_WIND_COMPATIBLE
#include <stdlib.h>
#endif

auto main() -> int 
{
#if OS_WIND_COMPATIBLE
  system("chcp 1251");
  SCREEN_CLEAR;
#else
  std::locale("ru_RU.UTF-8");
#endif
  std::cout << "Добро пожаловать в серверное приложение сетевого чата!" 
    << std::endl;
  std::cout << "Чтобы в процессе переписки выйти из чата введите exit" 
    << std::endl;
  std::cout << "Для продолжения придумайте и введите свой nickname: ";
  NetworkServer server;
  std::getline(std::cin, server.name_);
  size_t networkStatus = server.Listen();
  SCREEN_CLEAR;
  while (networkStatus == 0)
  {
    if (networkStatus == 0)
      networkStatus = server.Read();
    if (networkStatus == 0)
      networkStatus = server.Write();
  }
  server.Shutdown();
  return 0;
}