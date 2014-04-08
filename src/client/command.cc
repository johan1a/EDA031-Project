#include <algorithm>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include "command.h"
#include "syntax_exception.h"
#include "server_exception.h"
#include "../common/protocol.h"

using namespace std;

Command::Command(ClientCommandHandler& cch) : cmdHandler(cch) {}

vector<string> Command::list(vector<string>& tokens) {
	vector<string> result;
	if(tokens.size() == 1){
		result = cmdHandler.listGroups();
	}else {
		int groupIndex = stoi(tokens[1]);
		result = cmdHandler.listArticles(groupIndex);
	}
	return result;
}

vector<string> Command::read(vector<string>& tokens) {
	int groupIndex = stoi(tokens[1]);
	int articleIndex = stoi(tokens[2]);
	return cmdHandler.getArticle(groupIndex,articleIndex);
}

void Command::create(vector<string>& tokens) {
	int returnCode = -1;

	if(tokens.size() == 2){
		if(tokens[1] == "group"){ 
			string groupName;
			cout << "Enter group name: " << endl;
			cin >> groupName;
			returnCode = cmdHandler.createGroup(groupName);
		} else if (tokens[1] == "article") {
			string title, author, text;
			int index;
			
			cout << "Enter group index: " << endl;
			cin >> index;
			cout << "Enter article title: " << endl;
			cin >> title;
			cout << "Enter author: " << endl;
			cin >> author;
			string temp;
			string end = "done";
			while(temp != end) {
				cout << "Enter text: " << endl;
				cin >> temp;
				text = text + temp + '\n';
			}
			text = text.substr(0, text.length() - end.length());
			
			returnCode = cmdHandler.createArticle(index, title, author, text);
		} else {
			throw SyntaxException("Usage: create [group | article]");
		}
	} else {
		throw SyntaxException("Usage: create [group | article]");
	}
	if (returnCode == 0) {
		
	} else if (returnCode == Protocol::ERR_NG_DOES_NOT_EXIST) {
		throw ServerException("The news group does not exist.");
	}
}

void Command::del(vector<string>& tokens) {
	int returnCode = 1;
	if (tokens.size() >= 2) {
		if (tokens[1] == "group") {
			if (tokens.size() == 3) {
				try {
					returnCode = cmdHandler.deleteGroup(stoi(tokens[2]));
				} catch (const invalid_argument& ia) {
					throw SyntaxException("Usage: delete group <News Group ID>");
				} catch (const std::out_of_range& oor) {
					throw SyntaxException("Usage: delete group <News Group ID>");
				}
			} else {
				throw SyntaxException("Usage: delete group <News Group ID>");
			}
		} else if (tokens[1] == "article") {
			if (tokens.size() == 4) {
				try {
					returnCode = cmdHandler.deleteArticle(stoi(tokens[2]), stoi(tokens[3]));
				} catch (const invalid_argument& ia) {
					throw SyntaxException("Usage: delete article <News Group ID> <Article ID>");
				} catch (const std::out_of_range& oor) {
					throw SyntaxException("Usage: delete article <News Group ID> <Article ID>");
				}
			} else {
				throw SyntaxException("Usage: delete article <News Group ID> <Article ID>");
			}
		} else {
			throw SyntaxException("Usage: delete [group <News Group ID> | article <News Group ID> <Article ID>]");
		}
	} else {
		throw SyntaxException("Usage: delete [group <News Group ID> | article <News Group ID> <Article ID>]");
	}
}
