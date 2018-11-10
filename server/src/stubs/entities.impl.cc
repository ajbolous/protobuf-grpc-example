#include "entities.impl.h"

EntitiesApiImpl::EntitiesApiImpl(std::string &databaseAddress)
    : dbClient(database::protos::QueryApi::NewStub(grpc::CreateChannel(databaseAddress, grpc::InsecureChannelCredentials()))) {}

grpc::Status EntitiesApiImpl::GetEntity(grpc::ServerContext *context, const server::protos::EntityQueryRequest *request, common::protos::Entity *response)
{
    logging::Info("[GetEntity] Calling Query for ID " + request->id());

    database::protos::QueryRequest dbRequest;
    dbRequest.set_id(request->id());
    if (dbClient->Query(new grpc::ClientContext(), dbRequest, response).ok())
    {
        logging::Success("Entity Found");
        return grpc::Status::OK;
    }
    logging::Error("Entity Not Found");
    return grpc::Status(grpc::StatusCode::NOT_FOUND, "Server Couldn't find entity with given id");
}
grpc::Status EntitiesApiImpl::AddEntity(grpc::ServerContext *context, const common::protos::Entity *request, server::protos::EntityUpdatedResponse *response)
{
    response->set_issuccess(true);
    return grpc::Status::OK;
}