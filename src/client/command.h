#ifndef COMMAND_H
#define COMMAND_H
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>
#include <iterator>

using namespace std; //yolo

class Command{
	public:
		Command();
		Command(vector<string>& input) : tokens(input) {}
		virtual vector<string> execute(ClientCommandHandler& cmdHandler);
	protected:
		vector<string> tokens;
};

class ListCommand: public Command{
	public:
		ListCommand();
		ListCommand(vector<string>& input) : Command(input) {}

		vector<string> execute(ClientCommandHandler& cmdHandler) override {
			vector<string> result;
			if(tokens.size() == 1){
				result = cmdHandler.listGroups();
			}else {
				int groupIndex = stoi(tokens[1]);
				result = cmdHandler.listArticles(groupIndex);
			}
			return result;
		}
};

class ReadCommand: public Command{
public:
	ReadCommand();
	ReadCommand(vector<string>& input, vector<string>& prev) : Command(input), prevInput(prev) {}

	vector<string> execute(ClientCommandHandler& cmdHandler) override {
			if(prevInput[0] != "list"){
				// nu ere kokta flesket stekt
			}
			int groupIndex = stoi(prevInput[1]);
			int articleIndex = stoi(tokens[1]);
			return cmdHandler.getArticle(groupIndex,articleIndex);
	}
private:
	vector<string> prevInput;
};

class CreateCommand: public Command{
public:
	CreateCommand();
	CreateCommand(vector<string>& input) : Command(input) {}

	vector<string> execute(ClientCommandHandler& cmdHandler) override {
		int returnCode = -1;

		if(tokens.size() >= 3){
			if(tokens[1] == "group"){ 
				string cmd = "create group ";
				string groupName = accumulate(tokens.begin(), tokens.end(), string(" ")); //TODO joinar nog inte korrekt

				returnCode = cmdHandler.createGroup(groupName);
			}else if(tokens[1] == "article"){
				string title, author, text;
				int index;
				
				cout << "Enter group index: " << endl;
				cin >> index;
				cout << "Enter article title: " << endl;
				cin >> title;
				cout << "Enter author: " << endl;
				cin >> author;
				cout << "Enter text: " << endl; //TODO kommer krångla med newline, hur avsluta input? Alternativt fuck formatering...
				cin >> text;
				
				returnCode = cmdHandler.createArticle(index, title, author, text);
		}
		}else{
			//kasta nu gick det allt snett-exception
		}
		vector<string> result{to_string(returnCode)};
		return result;
	}
};

class DeleteCommand: public Command{
public:
	DeleteCommand();
	DeleteCommand(vector<string>& input, vector<string>& prev) : Command(input), prevInput(prev) {}

	vector<string> execute(ClientCommandHandler& cmdHandler) override {
		int returnCode = 1;
		if(tokens.size() == 3) {
			int index = stoi(tokens[2]);
			if(tokens[1] == "group"){ 
				returnCode = cmdHandler.deleteGroup(index);
			}else if (tokens[1] == "article"){
				if(prevInput[0]!="list"){
					//nejjj allt är förlorat
				}
				int groupIndex = stoi(prevInput[1]);
				returnCode = cmdHandler.deleteArticle(groupIndex, index);
			}	
		}
		vector<string> result{to_string(returnCode)};
		return result;
	}
private:
	vector<string> prevInput;
};
#endif