#include <fstream>
#include <iostream>

#include <grpcpp/server.h>
#include <grpcpp/server_builder.h>

#include "core/db_core.h"
#include "stubs/query_api.impl.h"

void InitServerData()
{
	std::fstream output("db.buf", std::ios::out | std::ios::binary);
	common::protos::Entity e;
	e.set_name("Bolous2");
	e.set_id("1");
	e.set_password("12356");
	if (!e.SerializeToOstream(&output))
	{
		std::cerr << "Failed to write address book." << std::endl;
	}
	output.close();
}

void AddService(grpc::ServerBuilder &builder, grpc::Service *service, std::string &&name)
{
	std::cout << "\t-Serving a new API: " << name << std::endl;
	builder.RegisterService(service);
}

int main(int argc, char **argv)
{
	InitServerData();
	std::string address("localhost:60060");
	std::string db_workspace("db.buf");

	std::cout << "Starting a new Database Core, Workspace: " << db_workspace << std::endl;
	core::DatabaseCore dbCore(db_workspace);

	std::cout << "Starting a new Database Server, Address: " << address << std::endl;
	grpc::ServerBuilder builder;
	builder.AddListeningPort(address, grpc::InsecureServerCredentials());

	AddService(builder, new QueryApiImpl(&dbCore), "QueryApi");

	std::unique_ptr<grpc::Server> server = builder.BuildAndStart();
	server->Wait();

	return 0;
}