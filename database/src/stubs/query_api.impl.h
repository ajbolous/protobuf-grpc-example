#ifndef DATABASE_STUBS_QUERY_API_IMPL_H
#define DATABASE_STUBS_QUERY_API_IMPL_H

#include <iostream>
#include "database/protos/query_api.grpc.pb.h"
#include "database/src/core/db_core.h"
#include "common/logging/logging.h"

class QueryApiImpl final : public database::protos::QueryApi::Service
{
  private:
    core::DatabaseCore *core = nullptr;

  public:
    QueryApiImpl(core::DatabaseCore *core_);
    grpc::Status Query(grpc::ServerContext *context, const database::protos::QueryRequest *request, common::protos::Entity *response) override;
};

#endif