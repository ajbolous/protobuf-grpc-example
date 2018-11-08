#ifndef DATABASE_CORE_DATABASECORE
#define DATABASE_CORE_DATABASECORE

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "database/protos/query_api.pb.h"
#include "common/logging/logging.h"

namespace core
{
class DatabaseCore
{
    std::string dbName;
    std::vector<common::protos::Entity> entites;
    void LoadDatabaseEnttities();

  public:
    DatabaseCore(const std::string &&dbName_);
    DatabaseCore(const std::string &dbName_);
    bool GetEntityById(const std::string &id, common::protos::Entity *entity);
};
}; // namespace core
#endif
