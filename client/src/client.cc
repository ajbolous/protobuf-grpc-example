#include <chrono>
#include <thread>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "server/protos/entities.grpc.pb.h"
#include "common/logging/logging.h"

int main(int argc, char **argv)
{
    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<server::protos::EntitiesApi::Stub> stub = server::protos::EntitiesApi::NewStub(channel);

    server::protos::EntityQueryRequest request;
    common::protos::Entity response;

    for (int i = 0; i < 10000; i++)
    {
        request.set_id(std::to_string(rand() % 3));
        grpc::ClientContext context;

        grpc::Status status = stub->GetEntity(&context, request, &response);
        if (status.ok())
            Logging::Success("Found Entity: (" + response.name() + ", " + response.password() + ")");
        else
        {
            Logging::Error("[ERROR] Entity Not Found: ", false);
            Logging::Warning(status.error_message());
        }
    }
    return 0;
}