#include "common/manager/server_manager.h"
#include "stubs/entities.impl.h"

int main(int argc, char **argv)
{
  std::string server_address("localhost:50050");
  std::string db_address("localhost:60060");
  manager::ServerManager server(server_address);
  server.AddService(new EntitiesApiImpl(db_address), "Entities");
  server.Start();
}