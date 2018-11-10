#include "db_core.h"

core::DatabaseCore::DatabaseCore(const std::string &dbFolderPath_) : dbFolderPath(dbFolderPath_)
{
  LoadDatabaseIndex();
}

core::DatabaseCore::DatabaseCore(const std::string &&dbFolderPath_) : DatabaseCore(dbFolderPath_) {}

void core::DatabaseCore::LoadDatabaseIndex()
{
  logging::Info("Starting a new Database Core, Workspace: " + dbFolderPath);

  std::fstream input(dbFolderPath + "/index.buf", std::ios::in | std::ios::binary);

  if (index.ParseFromIstream(&input))
  {
    input.close();
    logging::Success("Loaded database index, Total rows: " + std::to_string(index.indices().size()));
    return;
  }

  logging::Warning("No Databse Index was found, creating a new one");

  index = database::protos::DatabaseIndex();
  if (WriteDatabaseIndex())
    logging::Error("Unable to create a database index, Exiting...");
  exit(-1);
}

bool core::DatabaseCore::WriteDatabaseIndex()
{
  std::fstream output(dbFolderPath + "/index.buf", std::ios::out | std::ios::binary);
  if (index.SerializeToOstream(&output))
  {
    output.close();
    logging::Success("New database Index was created successfully.");
    return true;
  }
  return false;
}

bool core::DatabaseCore::LoadEntity(const std::string &filename, common::protos::Entity *entity)
{
  std::fstream input(dbFolderPath + "/" + filename, std::ios::in | std::ios::binary);

  if (entity->ParseFromIstream(&input))
  {
    input.close();
    logging::Success("Loaded database item " + filename);
    return true;
  }

  logging::Error("Unable to read item from database " + filename);
  return false;
}

bool core::DatabaseCore::EntryExists(const std::string &id)
{
  auto entryIndex = index.indices().find(id);
  if (entryIndex == index.indices().end())
  {
    logging::Warning("Unable to find id in database index , Id: " + id);
    return false;
  }
  return true;
}

bool core::DatabaseCore::GetEntityById(const std::string &id, common::protos::Entity *entity)
{
  if (EntryExists(id))
    return LoadEntity(index.indices().at(id).file(), entity);
  return false;
}

bool core::DatabaseCore::WriteEntity(const common::protos::Entity &entity)
{
  if (EntryExists(entity.id()))
  {
    logging::Warning("Entity with given id already exists updating! ID: " + entity.id());
  }
  else
  {
    database::protos::IndexEntry *entry = new database::protos::IndexEntry();
    entry->set_file("/" + entity.id() + ".buf");
    (*index.mutable_indices())[entity.id()] = *entry;
  }

  const database::protos::IndexEntry &entry = index.indices().at(entity.id());

  std::fstream output(dbFolderPath + entry.file(), std::ios::out | std::ios::binary);
  if (entity.SerializeToOstream(&output))
  {
    output.close();
    logging::Success("Entity updated succesfully");
  }

  return WriteDatabaseIndex();
}