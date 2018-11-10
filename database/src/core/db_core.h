#ifndef DATABASE_CORE_DATABASECORE
#define DATABASE_CORE_DATABASECORE

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

#include "database/protos/query_api.pb.h"
#include "database/protos/index.pb.h"
#include "common/logging/logging.h"

namespace core
{
class DatabaseCore
{
  std::string dbFolderPath;
  database::protos::DatabaseIndex index;
  void LoadDatabaseIndex();
  bool WriteDatabaseIndex();
  bool EntryExists(const std::string &id);
  bool LoadEntity(const std::string &filename, common::protos::Entity *entity);

public:
  DatabaseCore(const std::string &&dbFolderPath_);
  DatabaseCore(const std::string &dbFolderPath_);
  bool GetEntityById(const std::string &id, common::protos::Entity *entity);
  bool WriteEntity(const common::protos::Entity &entity);
};
}; // namespace core
#endif
