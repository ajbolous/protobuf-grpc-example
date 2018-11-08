#include <iostream>
#include <fstream>

#include "db_core.h"

namespace core
{
void DatabaseCore::LoadDatabaseEnttities()
{
  std::fstream input(dbName, std::ios::in | std::ios::binary);
  common::protos::Entity entity;
  entity.ParseFromIstream(&input);
  std::cout << entity.name() << std::endl;
  entites.push_back(entity);
}

bool DatabaseCore::GetEntityById(const std::string &id, common::protos::Entity *entity)
{
  for (common::protos::Entity &e : entites)
  {
    if (e.id().compare(id) == 0)
    {
      *entity = e;
      return true;
    }
  }
  return false;
}
} // namespace core