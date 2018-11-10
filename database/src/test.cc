#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "database/protos/query_api.grpc.pb.h"

int main(int argc, char **argv)
{
    auto channel = grpc::CreateChannel("localhost:60060", grpc::InsecureChannelCredentials());
    std::unique_ptr<database::protos::QueryApi::Stub> stub = database::protos::QueryApi::NewStub(channel);
    grpc::ClientContext(context);

    database::protos::QueryRequest request;
    request.set_id("entity id");

    common::protos::Entity e1;

    e1.set_id("entity id");
    e1.set_name("bolous-test");
    e1.set_address("address test");
    e1.set_password("password");

    database::protos::UpdateResponse response;
    stub->Insert(&context, e1, &response);

    grpc::ClientContext cont2;

    common::protos::Entity entity;
    std::cout << (stub->Query(&cont2, request, &entity).ok() ? "Success" : "Failed") << std::endl;

    std::cout << entity.name() << std::endl;
    std::cout << entity.password() << std::endl;
    std::cout << entity.address() << std::endl;
}