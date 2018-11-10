#include <grpcpp/grpcpp.h>
#include <grpcpp/channel.h>
#include "server/protos/entities.grpc.pb.h"
#include "database/protos/query_api.grpc.pb.h"
#include "common/logging/logging.h"

class EntitiesApiImpl final : public server::protos::EntitiesApi::Service
{
	std::unique_ptr<database::protos::QueryApi::Stub> dbClient;

  public:
	EntitiesApiImpl(std::string &databaseAddress);
	grpc::Status GetEntity(grpc::ServerContext *context, const server::protos::EntityQueryRequest *request, common::protos::Entity *response) override;
	grpc::Status AddEntity(grpc::ServerContext *context, const common::protos::Entity *request, server::protos::EntityUpdatedResponse *response) override;
};