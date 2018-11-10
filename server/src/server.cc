#include <sqlite3.h> 

#include "common/manager/server_manager.h"
#include "stubs/entities.impl.h"

int main(int argc, char **argv)
{
  std::string server_address("localhost:50050");
  std::string db_address("localhost:60060");

  sqlite3*db;
  if(sqlite3_open("test.db", &db))
    return -1;

  manager::ServerManager server(server_address);
  server.AddService(new EntitiesApiImpl(db_address), "Entities");
  server.Start();
  return 0;
}