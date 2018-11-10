#include <chrono>
#include <thread>
#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "server/protos/entities.grpc.pb.h"
#include "common/logging/logging.h"

int main(int argc, char **argv)
{
    auto channel = grpc::CreateChannel("localhost:50050", grpc::InsecureChannelCredentials());
    std::unique_ptr<server::protos::EntitiesApi::Stub> stub = server::protos::EntitiesApi::NewStub(channel);

    server::protos::EntityQueryRequest request;
    common::protos::Entity response;

    for (int i = 0; i < 10; i++)
    {
        request.set_id(std::to_string(rand() % 3));
        grpc::ClientContext context;

        grpc::Status status = stub->GetEntity(&context, request, &response);
        if (status.ok())
            logging::Success("Found Entity: (" + response.name() + ", " + response.password() + ")");
        else
        {
            logging::Error("Entity Not Found: ", false);
            logging::Warning(status.error_message());
        }
    }
    return 0;
}