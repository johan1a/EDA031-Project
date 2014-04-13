#include "news_server.h"
#include "main_database.h"

using namespace std;

int main(int argc, char* argv[]){
	MainDatabase mdb;
	NewsServer newsServer(argc, argv);
	newsServer.run(mdb);
}
