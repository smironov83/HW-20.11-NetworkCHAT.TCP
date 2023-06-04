#include "network_client.h"

auto main() -> int
{
#if OS_WIND_COMPATIBLE
  system("chcp 1251");
  system("cls");
#endif
  NetworkClient server;
  size_t networkStatus = server.Connect();
  while (networkStatus == 0)
  {
    networkStatus = server.Send();
    if (networkStatus == 0)
      networkStatus = server.Recv();
  }
  server.Shutdown();
  return 0;
}