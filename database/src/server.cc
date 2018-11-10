#include <fstream>
#include "core/db_core.h"
#include "common/manager/server_manager.h"
#include "stubs/query_api.impl.h"

int main(int argc, char **argv)
{
	std::string server_address("localhost:60060");
	std::string db_workspace("db");

	core::DatabaseCore dbCore(db_workspace);
	manager::ServerManager server(server_address);
	server.AddService(new QueryApiImpl(&dbCore), "QueryApiImpl");
	server.Start();
}
