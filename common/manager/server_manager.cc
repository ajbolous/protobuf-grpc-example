#include "server_manager.h"

namespace manager
{

ServerManager::ServerManager(std::string &address_) : address(address_)
{
    logging::Text("[Server] - Starting a new Server, Address: " + address);
    logging::Info("[Server] - Connecting to backend database, Address: " + address);
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
}

void ServerManager::AddService(grpc::Service *service, std::string &&name)
{
    logging::Info("\t[Server] - Serving a new Stub API: " + name);
    builder.RegisterService(service);
}

void ServerManager::Start()
{
    std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
    server->Wait();
}
} // namespace manager
