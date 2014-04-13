#ifndef NEWS_SERVER_H
#define NEWS_SERVER_H
#include "database.h"
#include "server_command_handler.h"
#include "../common/server.h"
#include "string"

class NewsServer{
public:
	NewsServer(int argc, char* argv[]);
	void run(Database& db);
private:
	int port = -1;
};
#endif