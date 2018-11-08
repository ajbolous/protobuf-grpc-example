#ifndef DATABASE_CORE_DATABASECORE
#define DATABASE_CORE_DATABASECORE

#include <iostream>
#include <string>
#include <vector>

#include "database/protos/query_api.pb.h"

namespace core
{
class DatabaseCore
{
    std::string dbName;
    std::vector<common::protos::Entity> entites;
    void LoadDatabaseEnttities();

  public:
    DatabaseCore(const std::string &&dbName_) : dbName(dbName_)
    {
        LoadDatabaseEnttities();
    }
    DatabaseCore(const std::string &dbName_) : dbName(dbName_)
    {
        LoadDatabaseEnttities();
    }
    bool GetEntityById(const std::string &id, common::protos::Entity *entity);
};
}; // namespace core
#endif
