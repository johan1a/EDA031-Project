#include "news_client.h"
#include <iostream>
#include <algorithm>
#include <vector>
#include <sstream>
#include <iterator>
#include "user_input_handler.h"
#include "../common/message_handler.h"
#include "client_command_handler.h"
#include "../common/exception/syntax_exception.h"
#include "../common/exception/news_group_does_not_exist_exception.h"
#include "../common/exception/article_does_not_exist_exception.h"
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
	UserInputHandler uih(cmdH);
	NewsClient client(uih);
	client.run();
}

NewsClient::NewsClient(UserInputHandler& h) : handler(h) {
	availableCommands += "Available commands: \n";
	availableCommands += "list\n";
	availableCommands += "list <newsgroup ID>\n";
	availableCommands += "read <newsgroup ID> <article ID>\n";
	availableCommands += "create group\n";
	availableCommands += "create article <newsgroup ID>\n";
	availableCommands += "delete group <newsgroup ID>\n";
	availableCommands += "delete article <newsgroup ID> <article ID>\n";
}

void NewsClient::run(){
	string input;
	vector<string> output;
	vector<string> tokens;
	bool closeRequested = false;
	cout << "Welcome!" << endl;
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
				output = handler.list(tokens);
			}else if (tokens[0] == "read"){
				output = handler.read(tokens);
			}else if(tokens[0] == "create"){
				handler.create(tokens);
				output.push_back("The creation was successful");
			}else if(tokens[0] == "delete"){
				handler.del(tokens);
				output.push_back("The deletion was successful");
			}else{
				output.push_back(availableCommands);
			}
		} catch(const SyntaxException& e) {
			output.push_back(e.msg);		
		} catch(const NewsGroupDoesNotExistException& e) {
			output.push_back(e.msg);		
		} catch(const ArticleDoesNotExistException& e) {
			output.push_back(e.msg);		
		}
	} else{
		output.push_back(availableCommands);
	}
	return output;
}
