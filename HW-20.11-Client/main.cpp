#include "network_client.h"
#if OS_WIND_COMPATIBLE

#endif

auto main() -> int
{
#if OS_WIND_COMPATIBLE
  system("chcp 1251");
  SCREEN_CLEAR;
#else
  std::locale("ru_RU.UTF-8");
#endif
  std::cout << "Добро пожаловать в клиентское приложение сетевого чата!" 
    << std::endl;
  std::cout << "Чтобы в процессе переписки выйти из чата введите exit"
    << std::endl;
  std::cout << "Для продолжения придумайте и введите свой nickname: ";
  NetworkClient client;
  std::getline(std::cin, client.name_);
  size_t networkStatus = client.Connect();
  while (networkStatus == 0)
  {
    if (networkStatus == 0)
      networkStatus = client.Write();
    if (networkStatus == 0)
      networkStatus = client.Read();
  }
  client.Shutdown();
  return 0;
}