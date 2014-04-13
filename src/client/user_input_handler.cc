#include <algorithm>
#include <iostream>
#include <sstream>
#include <stdexcept>
#include <iterator>
#include "user_input_handler.h"
#include "../common/protocol.h"

using namespace std;

UserInputHandler::UserInputHandler() {}

UserInputHandler::UserInputHandler(ClientCommandHandler& cch) : cmdHandler(cch) {}

vector<string> UserInputHandler::list(vector<string>& tokens) throw (ListSyntaxException, NewsGroupDoesNotExistException, ArticleDoesNotExistException, ConnectionClosedException, ProtocolViolationException){
	vector<string> result;
	if(tokens.size() == 1){
		result = cmdHandler.listGroups();
		if (result.size() == 0) {
			result.push_back("No news groups found.");
		}
	}else if (tokens.size() == 2) {
		try {
			int groupIndex = stoi(tokens[1]);
			result = cmdHandler.listArticles(groupIndex);
			if (result.size() == 0) {
				result.push_back("No articles found.");
			}
		} catch (const invalid_argument& ia) {
			throw ListSyntaxException();
		} catch (const std::out_of_range& oor) {
			throw ListSyntaxException();
		}
	} else {
		throw ListSyntaxException();
	}
	return result;
}

vector<string> UserInputHandler::read(vector<string>& tokens) throw (NewsGroupDoesNotExistException, ArticleDoesNotExistException, ReadSyntaxException, ConnectionClosedException, ProtocolViolationException) {
	int groupIndex = -1;
	int articleIndex = -1;
	if (tokens.size() == 3) {
		try {
			groupIndex = stoi(tokens[1]);
			articleIndex = stoi(tokens[2]);
		} catch (const invalid_argument& ia) {
			throw ReadSyntaxException();
		} catch (const std::out_of_range& oor) {
			throw ReadSyntaxException();
		}
	} else {
		throw ReadSyntaxException();
	}
	vector<string> output = cmdHandler.getArticle(groupIndex,articleIndex);
	return output;
}

void UserInputHandler::create(vector<string>& tokens) throw (CreateSyntaxException, NewsGroupDoesNotExistException, ConnectionClosedException, ProtocolViolationException){
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
			string indata;
			cout << "Enter group index: " << endl;
			getline(cin, indata);
			try{
				index=stoi(indata);
			} catch (const invalid_argument& ia) {
				throw CreateSyntaxException();
			} catch (const std::out_of_range& oor) {
				throw CreateSyntaxException();
			}
			cout << "Enter article title: " << endl;
			getline(cin, title);
			cout << "Enter author: " << endl;
			getline(cin, author);
			
			string endDelim = "done";
			cout << "Enter text (finish with line \"" + endDelim + "\"): " << endl;

			string temp;
			while(temp != endDelim) {
				getline(cin, temp);
				text += temp + '\n';
			}
			text = text.substr(0, text.length() - endDelim.length() - 1);
			returnCode = cmdHandler.createArticle(index, title, author, text);
		} else {
			throw CreateSyntaxException();
		}
	} else {
		throw CreateSyntaxException();
	}
	if (returnCode == Protocol::ERR_NG_DOES_NOT_EXIST) {
		throw NewsGroupDoesNotExistException();
	}
}

void UserInputHandler::del(vector<string>& tokens) throw (NewsGroupDoesNotExistException, ArticleDoesNotExistException, DeleteSyntaxException, ConnectionClosedException, ProtocolViolationException){
	int errorCode = 0;
	try {
		if(tokens.size() == 3 && tokens[1] == "group"){
			errorCode = cmdHandler.deleteGroup(stoi(tokens[2]));
		}else if (tokens.size() == 4 && tokens[1] == "article"){
			errorCode = cmdHandler.deleteArticle(stoi(tokens[2]), stoi(tokens[3]));
		}else{
			throw DeleteSyntaxException();
		}	
		if(errorCode == Protocol::ERR_NG_DOES_NOT_EXIST){
			throw NewsGroupDoesNotExistException();
		}else if(errorCode == Protocol::ERR_ART_DOES_NOT_EXIST){
			throw ArticleDoesNotExistException();
		}
	} catch (const invalid_argument& ia) {
		throw DeleteSyntaxException();
	} catch (const std::out_of_range& oor) {
		throw DeleteSyntaxException();
	}
}
