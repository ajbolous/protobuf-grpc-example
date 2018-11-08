#include <iostream>
#include <grpc/grpc.h>

#include "database/protos/query_api.grpc.pb.h"

#include "../core/db_core.h"

class QueryApiImpl final : public database::protos::QueryApi::Service
{
  private:
    core::DatabaseCore *core = nullptr;

  public:
    QueryApiImpl(core::DatabaseCore *core_) : core(core_) {}

    grpc::Status Query(grpc::ServerContext *context, const database::protos::QueryRequest *request, common::protos::Entity *response) override
    {
        std::cout << "[Query] Querying for ID: " << request->id();
        if (core->GetEntityById(request->id(), response))
        {
            std::cout << "\t Found Entity: " << response->name() << std::endl;
            return grpc::Status::OK;
        }
        std::cout << "\t \033[1;31m Entity Not Found" << "\033[0m" << std::endl;
        return grpc::Status::CANCELLED;
    }
};