#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "database/protos/query_api.grpc.pb.h"
#include "common/logging/logging.h"
#include "common/protos/entity.pb.h"

common::protos::Entity CreateTestEntity()
{
    common::protos::Entity entity;
    entity.set_id("entity id");
    entity.set_name("bolous-test");
    entity.set_address("address test");
    entity.set_password("password3232");
    return entity;
}

int main(int argc, char **argv)
{
    auto channel = grpc::CreateChannel("localhost:60060", grpc::InsecureChannelCredentials());
    std::unique_ptr<database::protos::QueryApi::Stub> stub = database::protos::QueryApi::NewStub(channel);

    database::protos::QueryRequest request;
    request.set_id("entity id");

    database::protos::UpdateResponse response;

    common::protos::Entity entity = CreateTestEntity();

    if (stub->Insert(new grpc::ClientContext(), entity, &response).ok())
        if (stub->Query(new grpc::ClientContext(), request, &entity).ok())
            logging::Info("Name: " + entity.name() + ", Password: " + entity.password());
}