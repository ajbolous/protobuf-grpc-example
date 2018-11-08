#include <iostream>
#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "server/protos/entities.grpc.pb.h"
#include "database/protos/query_api.grpc.pb.h"

class EntitiesApiImpl final : public server::protos::EntitiesApi::Service
{
  std::unique_ptr<database::protos::QueryApi::Stub> dbClient;

public:
  EntitiesApiImpl(std::string &databaseAddress) : dbClient(database::protos::QueryApi::NewStub(grpc::CreateChannel(databaseAddress, grpc::InsecureChannelCredentials())))
  {
  }

  grpc::Status GetEntity(grpc::ServerContext *context, const server::protos::EntityQueryRequest *request, common::protos::Entity *response) override
  {
    std::cout << "[GetEntity] Calling Query for ID: " << request->id();
    grpc::ClientContext clientContext;

    database::protos::QueryRequest dbRequest;
    dbRequest.set_id(request->id());
    if (dbClient->Query(&clientContext, dbRequest, response).ok())
    {
      std::cout << "\t Found Entity: " << response->name() << std::endl;
      return grpc::Status::OK;
    }

    std::cout << "\t \033[1;31m Entity Not Found" << "\033[0m" << std::endl;
    return grpc::Status(grpc::StatusCode::NOT_FOUND, "Entity Not Found");
  }
  grpc::Status AddEntity(grpc::ServerContext *context, const common::protos::Entity *request, server::protos::EntityUpdatedResponse *response) override
  {
    response->set_issuccess(true);
    return grpc::Status::OK;
  }
};