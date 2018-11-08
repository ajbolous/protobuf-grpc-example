
#include <iostream>

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "stubs/entities.impl.h"

void AddService(grpc::ServerBuilder &builder, grpc::Service* service, std::string &&name)
{
  std::cout << "\t-Serving a new Stub API: " << name << std::endl;
  builder.RegisterService(service);
}

int main(int argc, char **argv)
{
  std::string server_address("localhost:50051");
  std::string db_address("localhost:60060");

  std::cout << "Starting a new Server, Address: " << server_address << std::endl;
    std::cout << "Connecting to backend database, Address: " << db_address << std::endl;

  grpc::ServerBuilder builder;
  builder.AddListeningPort(server_address, grpc::InsecureServerCredentials());
  AddService(builder, new EntitiesApiImpl(db_address), "Entities");
  std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
  server->Wait();
  
  return 0;
}