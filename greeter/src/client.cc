#include <memory>

#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "greeter/proto/greet.grpc.pb.h"

int main(int argc, char **argv)
{

    auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
    std::unique_ptr<proto::Greeter::Stub> stub = proto::Greeter::NewStub(channel);

    proto::GreetRequest request;
    proto::GreetReply reply;
    std::string line;
    request.set_name("bolous");
    for (int i = 0; i < 10; i++)
    {
        grpc::ClientContext(context);
        stub->SayHello(&context, request, &reply);
        std::cout << reply.message() << std::endl;
    }
}