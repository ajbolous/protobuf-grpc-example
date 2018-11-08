#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "server/protos/entities.grpc.pb.h"

int main(int argc, char **argv)
{
    if (argc < 2)
        return -1;
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<server::protos::EntitiesApi::Stub> stub = server::protos::EntitiesApi::NewStub(channel);


    server::protos::EntityQueryRequest request;

    request.set_id(argv[1]);

    grpc::ClientContext context;
    
    common::protos::Entity response;

    grpc::Status status = stub->GetEntity(&context, request, &response);
    if(status.ok())
        std::cout << response.name() << ", " << response.password() << std::endl;
    else
        std::cout << "\033[1;31m" << status.error_message() << "\033[0m" << std::endl;

    return 0;
}