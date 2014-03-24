#include "client.h"
#include <iostream>
#include <algorithm>
#include <sstream>
#include <iterator>
#include "command.h"
using namespace std;

int main(){
	Client client;
	client.run();
} 

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

	Command c;
	if(tokens[0] == "list"){
		c = ListCommand(tokens);
	}else if (tokens[0] == "read"){
		c = ReadCommand(tokens,prevInput);
	}else if(tokens[0] == "create"){
		c = CreateCommand(tokens);
	}else if(tokens[0] == "delete"){
		c = DeleteCommand(tokens,prevInput);
	}
	prevInput = tokens;
	return c.execute(cmdHandler);
}