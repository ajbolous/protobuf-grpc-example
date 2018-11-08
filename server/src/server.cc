
#include <iostream>

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "stubs/entities.impl.h"
#include "common/logging/logging.h"

void AddService(grpc::ServerBuilder &builder, grpc::Service *service, std::string &&name)
{
  Logging::Info("\tServing a new Stub API: " + name);
  builder.RegisterService(service);
}

int main(int argc, char **argv)
{
  std::string server_address("localhost:50051");
  std::string db_address("localhost:60060");

  Logging::Info("Starting a new Server, Address: " + server_address);
  Logging::Info("Connecting to backend database, Address: " + db_address);

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  AddService(builder, new EntitiesApiImpl(db_address), "Entities");
  std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
  server->Wait();

  return 0;
}