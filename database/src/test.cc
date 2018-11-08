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
    request.set_id("1");

    common::protos::Entity entity;
    std::cout << (stub->Query(&context, request, &entity).ok() ? "Success" : "Failed") << std::endl; 

    std::cout << entity.name() << std::endl;
    std::cout << entity.password() << std::endl;
}