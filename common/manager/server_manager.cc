#include "server_manager.h"

manager::ServerManager::ServerManager(std::string &address_) : address(address_)
{
    logging::Info("[Server] - Starting a new gRPC Server, Address: " + address);
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
}

void manager::ServerManager::AddService(grpc::Service *service, std::string &&name)
{
    logging::Info("[Server] - Serving a new Stub API " + name);
    builder.RegisterService(service);
}

void manager::ServerManager::Start()
{
    logging::Info("[Server] - Starting server and waiting for connections..");
    std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
    server->Wait();
}