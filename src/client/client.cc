#include "client.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "command.h"
#include "client_command_handler.h"
#include "syntax_exception.h"
using namespace std;

int main(int argc, char* argv[]) {
	if (argc != 3) {
		cerr << "Usage: " << argv[0] << " host-name port-number" << endl;
		exit(1);
	}
	int port = -1;
	try {
		port = stoi(argv[2]);
	} catch (exception& e) {
		cerr << "Wrong port number. " << e.what() << endl;
		exit(1);
	}
		Connection conn(argv[1], port);
	if (!conn.isConnected()) {
		cerr << "Connection attempt failed" << endl;
		exit(1);
	}
	ClientCommandHandler cmdH(conn);
	Command cmd(cmdH);
	Client client(cmd);
	client.run();
}

Client::Client(Command& cmd) : com(cmd) {}

void Client::run(){
	string input;
	vector<string> output;
	while (input != "exit"){
		try {
			cin >> input;
			output = executeCommand(input);
			for_each(output.begin(), output.end(), [](string &s){ cout << s << endl; });
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

vector<string> Client::executeCommand(string& input){
	vector<string> tokens;
	istringstream iss(input);

	/* lägger in alla ord från input i tokens */
	copy(istream_iterator<string>(iss), istream_iterator<string>(),
       back_inserter<vector<string> >(tokens));

	if(tokens.size() != 0){
		try{
			vector<string> success;
			if(tokens[0] == "list"){
				return com.list(tokens);

			}else if (tokens[0] == "read"){
				return com.read(tokens);

			}else if(tokens[0] == "create"){
				com.create(tokens);
				success.push_back("The creation was successful");
				return success;

			}else if(tokens[0] == "delete"){
				com.del(tokens);
				success.push_back("The deletion was successful");
				return success;
			}
		} catch(const SyntaxException& se) {
			vector<string> res;
			res.push_back(se.msg);		
			return res;
		}

	} else{
		vector<string> res2;
		res2.push_back("Available commands: ");
		res2.push_back("list");
		res2.push_back("list <News Group ID>");
		res2.push_back("read <News Group ID> <Article ID>");
		res2.push_back("create group");
		res2.push_back("create article <News Group ID>");
		res2.push_back("delete group <News Group ID>");
		res2.push_back("delete article <News Group ID> <Article ID>");
		return res2;
	}
}


