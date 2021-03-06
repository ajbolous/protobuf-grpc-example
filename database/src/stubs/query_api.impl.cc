#include "query_api.impl.h"

QueryApiImpl::QueryApiImpl(core::DatabaseCore *core_) : core(core_) {}

grpc::Status QueryApiImpl::Query(grpc::ServerContext *context, const database::protos::QueryRequest *request, common::protos::Entity *response)
{
    logging::Info("[Query] Querying for ID: " + request->id());

    if (core->GetEntityById(request->id(), response))
    {
        logging::Success("\tFound Entity:" + response->name());
        return grpc::Status::OK;
    }
    logging::Error("\tEntity Not Found");
    return grpc::Status(grpc::StatusCode::NOT_FOUND, "Could'nt find entity with given id");
}

grpc::Status QueryApiImpl::Insert(grpc::ServerContext *context, const common::protos::Entity *entity, database::protos::UpdateResponse *response)
{
    logging::Info("[Insert] Inserting a new entity: " + entity->id());

    if (core->WriteEntity(*entity))
    {
        logging::Success("Inserted new Entity:" + entity->name());
        return grpc::Status::OK;
    }

    logging::Error("Unable to inesrt Entity with Id: " + entity->id());
    return grpc::Status(grpc::StatusCode::NOT_FOUND, "Unable to inesrt Entity with given id");
}
