#include "../common/connection.h"
#include "../common/server.h"
#include "../common/connection_closed_exception.h"
#include "../common/protocol_violation_exception.h"
#include "cache_database.h"
#include "server_command_handler.h"
#include <iostream>
#include <string>
#include <stdexcept>
#include <memory>
#include <cstdlib>

using namespace std;

int main(int argc, char* argv[]){
	if (argc != 2) {
		cerr << "Usage: myserver port-number" << endl;
		exit(1);
	}
	int port = -1;
	try {
		port = stoi(argv[1]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
	Server server(port);
	if (!server.isReady()) {
		cerr << "Server initialization error." << endl;
		exit(1);
	}
	CacheDatabase cDb;
	while (true) {
			shared_ptr<Connection> conn = server.waitForActivity();
		if (conn != nullptr) {
			MessageHandler msgH(*conn);
			ServerCommandHandler sCmdH(msgH, cDb);
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
