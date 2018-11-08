
#ifndef COMMON_MANAGER_SERVER_MANAGER_H
#define COMMON_MANAGER_SERVER_MANAGER_H

#include <iostream>
#include <string>

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "common/logging/logging.h"

namespace manager
{
class ServerManager
{
    std::string address;
    grpc::ServerBuilder builder;
    std::unique_ptr<grpc::Server> server;

  public:
    ServerManager(std::string &address_);
    void AddService(grpc::Service *service, std::string &&name);
    void Start();
};
} // namespace manager

#endif