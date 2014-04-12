#include "news_client.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include "command.h"
#include "../common/message_handler.h"
#include "client_command_handler.h"
#include "syntax_exception.h"
#include "server_exception.h"
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
	MessageHandler mh(conn);
	ClientCommandHandler cmdH(mh);
	Command cmd(cmdH);
	NewsClient client(cmd);
	client.run();
}

NewsClient::NewsClient(Command& cmd) : com(cmd) {}

void NewsClient::run(){
	string input;
	vector<string> output;
	vector<string> tokens;
	bool closeRequested = false;
	while (!closeRequested){
		try {
			tokens.clear();
			string tmp;
			cout << "> ";
			getline(cin, tmp);
			stringstream ss(tmp);
			istream_iterator<string> begin(ss);
			istream_iterator<string> end;
			vector<string> tokens(begin, end);
			if(tokens.size() == 1 && tokens[0] == "exit") {
				closeRequested = true;
			} else {
				output = executeCommand(tokens);
				for_each(output.begin(), output.end(), [](string &s){ cout << s << endl; });
			}
		} catch (ConnectionClosedException&) {
			cout << " no reply from server. Exiting." << endl;
			exit(1);
		}
	}
}

vector<string> NewsClient::executeCommand(vector<string> tokens){
	vector<string> output;
	if(tokens.size() != 0){
		try{
			if(tokens[0] == "list"){
				output = com.list(tokens);
			}else if (tokens[0] == "read"){
				output = com.read(tokens);
			}else if(tokens[0] == "create"){
				com.create(tokens);
				output.push_back("The creation was successful");
			}else if(tokens[0] == "delete"){
				com.del(tokens);
				output.push_back("The deletion was successful");
			}else{
				output = showAvailableCommands();
			}
		} catch(const SyntaxException& se) {
			output.push_back(se.msg);		
		} catch(const ServerException& serverE) {
			output.push_back(serverE.msg);		
		}
	} else{
		output = showAvailableCommands();
	}
	return output;
}

vector<string> NewsClient::showAvailableCommands(){
	vector<string> res;
	res.push_back("Available commands: ");
	res.push_back("list");
	res.push_back("list <newsgroup ID>");
	res.push_back("read <newsgroup ID> <article ID>");
	res.push_back("create group");
	res.push_back("create article <newsgroup ID>");
	res.push_back("delete group <newsgroup ID>");
	res.push_back("delete article <newsgroup ID> <article ID>");
	return res;
}

