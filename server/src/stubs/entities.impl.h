#include <iostream>
#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>

#include "server/protos/entities.grpc.pb.h"
#include "database/protos/query_api.grpc.pb.h"
#include "common/logging/logging.h"

class EntitiesApiImpl final : public server::protos::EntitiesApi::Service
{
	std::unique_ptr<database::protos::QueryApi::Stub> dbClient;

  public:
	EntitiesApiImpl(std::string &databaseAddress) : dbClient(database::protos::QueryApi::NewStub(grpc::CreateChannel(databaseAddress, grpc::InsecureChannelCredentials()))) {}

	grpc::Status GetEntity(grpc::ServerContext *context, const server::protos::EntityQueryRequest *request, common::protos::Entity *response) override
	{
		Logging::Info("[GetEntity] Calling Query for ID " + request->id(), false);
		grpc::ClientContext clientContext;

		database::protos::QueryRequest dbRequest;
		dbRequest.set_id(request->id());
		if (dbClient->Query(&clientContext, dbRequest, response).ok())
		{
			Logging::Success("\tFound Entity");
			return grpc::Status::OK;
		}
		Logging::Error("\tEntity Not Found");
		return grpc::Status(grpc::StatusCode::NOT_FOUND, "Server Couldn't find entity with given id");
	}
	grpc::Status AddEntity(grpc::ServerContext *context, const common::protos::Entity *request, server::protos::EntityUpdatedResponse *response) override
	{
		response->set_issuccess(true);
		return grpc::Status::OK;
	}
};