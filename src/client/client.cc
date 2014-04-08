#include "client.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "command.h"
#include "syntax_exception.h"
using namespace std;

int main(){
	Client client;
	client.run();
} 

Client::Client(){}

void Client::run(){
	bool isConnected = true;
	string host, port;

	cout << "Enter host name: " << endl;
	cin >> host;

	cout << "Enter port nbr: "<< endl;
	cin >> port;

	Connection conn(host.c_str(), stoi(port)); //TODO fult med c_str()
	ClientCommandHandler cmdHandler(conn);

	string input;
	vector<string> output;
	while (isConnected){
		cin >> input;

		output = executeCommand(input);
		for_each(output.begin(), output.end(), [](string &s){ cout << s << endl; });

		isConnected = false; //TODO fixa kommando för att stänga av programmet perhaps
	}
}

vector<string> Client::executeCommand(string& input){
	vector<string> tokens;
	istringstream iss(input);

	/* lägger in alla ord från input i tokens */
	copy(istream_iterator<string>(iss), istream_iterator<string>(),
       back_inserter<vector<string> >(tokens));
	
	Command c(cmdHandler);
	if(tokens.size() != 0){
		try{
			vector<string> success;
			if(tokens[0] == "list"){
				return c.list(tokens);

			}else if (tokens[0] == "read"){
				return c.read(tokens);

			}else if(tokens[0] == "create"){
				c.create(tokens);
				success.push_back("The creation was successful");
				return success;

			}else if(tokens[0] == "delete"){
				c.del(tokens);
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


