#include "news_server.h"
#include "../common/connection.h"
#include "../common/server.h"
#include "../common/exception/connection_closed_exception.h"
#include "../common/exception/protocol_violation_exception.h"
#include "cache_database.h"
#include <iostream>
#include <stdexcept>
#include <memory>
#include <cstdlib>

using namespace std;

NewsServer::NewsServer(int argc, char* argv[]) {
	if (argc != 2) {
		cerr << "Usage: "<< argv[0] << " port-number" << endl;
		exit(1);
	}
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}	
}

void NewsServer::run(Database& database){
	MessageHandler msgH;
	ServerCommandHandler sCmdH(msgH, database) ;
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}
	while (true) {
		shared_ptr<Connection> conn = server.waitForActivity();
		if (conn != nullptr) {
			msgH.changeConnection(*conn);
			try {
				sCmdH.newMessage();
			} catch (ConnectionClosedException& e) {
				server.deregisterConnection(conn);
				cout << "Client closed connection" << endl;
			} catch (ProtocolViolationException& e) {
				server.deregisterConnection(conn);
				cout << "Client did not follow the protocol" << endl;
			}
		} else {
			conn = make_shared<Connection>();
			server.registerConnection(conn);
			cout << "New client connects" << endl;
		}
	}
}
