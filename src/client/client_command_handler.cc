#include "client_command_handler.h"
#include "connection.h"
#include <string>

using namespace std;

ClientCommandHandler::ClientCommandHandler(){
	Connection conn;
	//messageHandler(conn);
}

string ClientCommandHandler::listGroups(){
	return "";	
}

int ClientCommandHandler::createGroup(string title){
	return 1;
}

int ClientCommandHandler::deleteGroup(int groupIndex){
	return 1;
}

string ClientCommandHandler::listArticles(int groupIndex){
	return "";
}

int ClientCommandHandler::createArticle(int groupIndex, string title, string author, string text){
	return 1;
}

int ClientCommandHandler::deleteArticle(int groupIndex, int articleIndex){
	return 1;
}

string ClientCommandHandler::getArticle(int groupIndex, int articleIndex){
	return "";
}

int ClientCommandHandler::getArticleId(int articleIndex){
	return 1;
}

void ClientCommandHandler::checkCode(string method, int expectedCode, int code){

}

void ClientCommandHandler::checkCondition(bool, string method, string message){

}
