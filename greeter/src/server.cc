#include <iostream>

#include <grpc/grpc.h>
#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "greeter/proto/greet.grpc.pb.h"

class GreeterImpl final : public proto::Greeter::Service
{
public:
  grpc::Status SayHello(grpc::ServerContext *context, const proto::GreetRequest *request, proto::GreetReply *response)
  {
    std::cout << "Client " << request->name() << " connected From Normal" << std::endl;
    return SendAHelloMessage("Hello from normal Stub : " + request->name(), response);
  }

  grpc::Status SayHelloVoid(grpc::ServerContext *context, const proto::GreetRequest *request, proto::GreetReply *response)
  {
    std::cout << "Client " << request->name() << " connected From Void" << std::endl;
    return SendAHelloMessage("Hello from void Stub : " + request->name(), response);
  }

private:
  grpc::Status SendAHelloMessage(std::string &&message, proto::GreetReply *response)
  {
    response->set_message(message);
    return grpc::Status::OK;
  }
};

class ServerManager
{
private:
  grpc::ServerBuilder builder;
  std::unique_ptr<grpc::Server> server;

public:
  ServerManager(std::string &&address)
  {
    std::cout << "Starting a new Server on port " << address << std::endl;
    builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  }

  void AddService(grpc::Service *service)
  {

    std::cout << "\t-Adding a new Stub " << std::endl;
    builder.RegisterService(service);
  }

  void Start()
  {
    server = builder.BuildAndStart();
    server->Wait();
  }
};

int main(int argc, char **argv)
{
  ServerManager server("localhost:50051");
  server.AddService(new GreeterImpl());
  server.Start();
  return 0;
}