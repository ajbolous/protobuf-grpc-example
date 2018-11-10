#include "server_manager.h"

manager::ServerManager::ServerManager(std::string &address_) : address(address_)
{
    logging::Text("[Server] - Starting a new Server, Address: " + address);
    logging::Text("[Server] - Connecting to backend database, Address: " + address);
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
}

void manager::ServerManager::AddService(grpc::Service *service, std::string &&name)
{
    logging::Info("\t[Server] - Serving a new Stub " + name);
    builder.RegisterService(service);
}

void manager::ServerManager::Start()
{
    std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
    server->Wait();
}