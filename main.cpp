#include "network_server.h"

auto main() -> int 
{
#if OS_WIND_COMPATIBLE
  system("chcp 1251");
  system("cls");
#endif
  NetworkServer client;
  size_t networkStatus = client.Listen();
  while (networkStatus == 0)
  {
    networkStatus = client.Recv();
    if (networkStatus == 0)
      networkStatus = client.Send();
  }
  client.Shutdown();
  return 0;
}