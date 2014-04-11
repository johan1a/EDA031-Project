#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include "command.h"
#include "syntax_exception.h"
#include "server_exception.h"
#include "../common/protocol.h"

using namespace std;

Command::Command() {}

Command::Command(ClientCommandHandler& cch) : cmdHandler(cch) {}

vector<string> Command::list(vector<string>& tokens) {
	vector<string> result;
	if(tokens.size() == 1){
		result = cmdHandler.listGroups();
	}else if (tokens.size() == 2) {
		try {
			int groupIndex = stoi(tokens[1]);
			result = cmdHandler.listArticles(groupIndex);
		} catch (const invalid_argument& ia) {
			throw SyntaxException("Usage: [list | list <News Group ID>]");
		} catch (const std::out_of_range& oor) {
			throw SyntaxException("Usage: [list | list <News Group ID>]");
		}
	} else {
		throw SyntaxException("Usage: [list | list <News Group ID>]");
	}
	return result;
}

vector<string> Command::read(vector<string>& tokens) {
	int groupIndex = -1;
	int articleIndex = -1;
	if (tokens.size() == 3) {
		try {
			groupIndex = stoi(tokens[1]);
			articleIndex = stoi(tokens[2]);
		} catch (const invalid_argument& ia) {
			throw SyntaxException("Usage: read <News Group ID> <Article ID>");
		} catch (const std::out_of_range& oor) {
			throw SyntaxException("Usage: read <News Group ID> <Article ID>");
		}
	} else {
		throw SyntaxException("Usage: read <News Group ID> <Article ID>");
	}
	return cmdHandler.getArticle(groupIndex,articleIndex);
}

void Command::create(vector<string>& tokens) {
	int returnCode = -1;

	if(tokens.size() == 2){
		if(tokens[1] == "group"){ 
			string groupName;
			cout << "Enter group name: " << endl;
			getline(cin, groupName);
			returnCode = cmdHandler.createGroup(groupName);
		} else if (tokens[1] == "article") {
			string title, author, text;
			int index;
			string ind;
			cout << "Enter group index: " << endl;
			//cin >> index;
			getline(cin, ind);
			try{
				index=stoi(ind);
			} catch (const invalid_argument& ia) {
				throw SyntaxException("Expected a News Group ID");
			} catch (const std::out_of_range& oor) {
				throw SyntaxException("Expected a News Group ID");
			}
			cout << "Enter article title: " << endl;
			getline(cin, title);
			cout << "Enter author: " << endl;
			getline(cin, author);
			string temp;
			string end = "done";
			cout << "Enter text: " << endl;
			while(temp != end) {
				getline(cin, temp);
				text = text + temp + '\n';
			}
			text = text.substr(0, text.length() - end.length() - 1);
			
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
	if (tokens.size() >= 2) {
		if (tokens[1] == "group") {
			if (tokens.size() == 3) {
				try {
					if(cmdHandler.deleteGroup(stoi(tokens[2])) != 0) {
						throw ServerException("The news group does not exist.");
					}
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
					int error = cmdHandler.deleteArticle(stoi(tokens[2]), stoi(tokens[3]));
					if(error == Protocol::ERR_NG_DOES_NOT_EXIST) {
						throw ServerException("The news group does not exist.");
					} else if (error == Protocol::ERR_ART_DOES_NOT_EXIST) {
						throw ServerException("The article does not exist.");
					}
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
