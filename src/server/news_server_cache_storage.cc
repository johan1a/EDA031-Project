#include "news_server.h"
#include "cache_database.h"

using namespace std;

int main(int argc, char* argv[]){
	CacheDatabase cdb;
	NewsServer newsServer(argc, argv);
	newsServer.run(cdb);
}
