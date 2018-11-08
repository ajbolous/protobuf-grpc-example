#include <fstream>
#include "core/db_core.h"
#include "common/manager/server_manager.h"
#include "stubs/query_api.impl.h"

void InitServerData()
{
	std::fstream output("db.buf", std::ios::out | std::ios::binary);
	common::protos::Entity e;
	e.set_name("Bolous2");
	e.set_id("1");
	e.set_password("12356");
	if (!e.SerializeToOstream(&output))
		logging::Error("Failed to read Entity buffer.");
	output.close();
}

int main(int argc, char **argv)
{
	std::string server_address("localhost:60060");
	std::string db_workspace("db.buf");
	
	InitServerData();
	core::DatabaseCore dbCore(db_workspace);
	manager::ServerManager server(server_address);
	server.AddService(new QueryApiImpl(&dbCore), "QueryApiImpl");
	server.Start();

	return 0;
}
