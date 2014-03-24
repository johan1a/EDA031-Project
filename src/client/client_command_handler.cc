#include "client_command_handler.h"
#include "../common/connection.h"
#include "../common/protocol.h"
#include <string>

using namespace std;

ClientCommandHandler::ClientCommandHandler(){
	Connection conn;
	messageHandler = MessageHandler(conn);
}

vector<string> ClientCommandHandler::listGroups() throw ( ConnectionClosedException){
	messageHandler.sendCode(Protocol::COM_LIST_NG);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	checkCode("List groups", Protocol::ANS_LIST_NG, code);

	int nbrGroups = messageHandler.recvIntParameter();
	checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
	groupIds = vector<int>();
	vector<string> groupNames;
	for(int i = 0; i < nbrGroups; ++i){
		groupIds[i] = messageHandler.recvIntParameter();
		groupNames[i] = messageHandler.recvStringParameter();

	}
	code = messageHandler.recvCode();
	checkCode("List groups", Protocol::ANS_END, code);
	return groupNames;	
}

int ClientCommandHandler::createGroup(string title) throw(ConnectionClosedException) {		
	messageHandler.sendCode(Protocol::COM_CREATE_NG);
	messageHandler.sendStringParameter(title);
	messageHandler.sendCode(Protocol::COM_END);
	
	int errorCode = 0;
	int code = messageHandler.recvCode();
	checkCode("Create group", Protocol::ANS_CREATE_NG, code);
	code = messageHandler.recvCode();

	if (code != Protocol::ANS_ACK) {
		checkCondition(code == Protocol::ANS_NAK, "Create group",
				"Did not receive ANS_ACK or ANS_NAK");
		errorCode = messageHandler.recvCode();
	}

	code = messageHandler.recvCode();
	checkCode("Create group", Protocol::ANS_END, code);
	return errorCode;
}

int ClientCommandHandler::deleteGroup(int groupIndex)  throw (ConnectionClosedException,
			ProtocolViolationException ){
	int groupId = getGroupId(groupIndex);

	messageHandler.sendCode(Protocol::COM_DELETE_NG);
	messageHandler.sendIntParameter(groupId);
	messageHandler.sendCode(Protocol::COM_END);

	int errorCode = 0;
	
	int code = messageHandler.recvCode();
	checkCode("Delete group", Protocol::ANS_DELETE_NG, code);
	code = messageHandler.recvCode();
	if (code != Protocol::ANS_ACK) {
		checkCondition(code == Protocol::ANS_NAK, "Create group",
				"Did not receive ANS_ACK or ANS_NAK");
		errorCode = messageHandler.recvCode();
	}
	code = messageHandler.recvCode();
	checkCode("Delete group", Protocol::ANS_END, code);
	
	return errorCode;
}

vector<string> ClientCommandHandler::listArticles(int groupIndex)  throw ( ConnectionClosedException){
	int groupId = getGroupId(groupIndex);

	messageHandler.sendCode(Protocol::COM_LIST_ART);
	messageHandler.sendIntParameter(groupId);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	checkCode("List articles", Protocol::ANS_LIST_ART, code);
	code = messageHandler.recvCode();
	if (code != Protocol::ANS_ACK) {
		checkCondition(code == Protocol::ANS_NAK, "Create group",
				"Did not receive ANS_ACK or ANS_NAK");
		code = messageHandler.recvCode(); // error code
		code = messageHandler.recvCode(); // hopefully ANS_NAK, not checked
	
		return vector<string>();
	}
	int nbrArticles = messageHandler.recvIntParameter();
	checkCondition(nbrArticles >= 0, "List articles",
			"Number of groups < 0");
	vector<int> articleIds;
	vector<string> articleNames;
	for (int i = 0; i < nbrArticles; i++) {
		articleIds[i] = messageHandler.recvIntParameter();
		articleNames[i] = messageHandler.recvStringParameter();
	}
	code = messageHandler.recvCode();
	checkCode("List articles", Protocol::ANS_END, code);

	return articleNames;
}

int ClientCommandHandler::createArticle(int groupIndex, string title, string author, string text) throw (ConnectionClosedException,
			ProtocolViolationException){
	int groupId = getGroupId(groupIndex);
	messageHandler.sendCode(Protocol::COM_CREATE_ART);
	messageHandler.sendIntParameter(groupId);
	messageHandler.sendStringParameter(title);
	messageHandler.sendStringParameter(author);
	messageHandler.sendStringParameter(text);
	messageHandler.sendCode(Protocol::COM_END);

	int errorCode = 0;
	int code = messageHandler.recvCode();
	checkCode("Create article", Protocol::ANS_CREATE_ART, code);
	code = messageHandler.recvCode();
	if (code != Protocol::ANS_ACK) {
		checkCondition(code == Protocol::ANS_NAK, "Create group",
				"Did not receive ANS_ACK or ANS_NAK");
		errorCode = messageHandler.recvCode();
	}
	code = messageHandler.recvCode();
	checkCode("Create article", Protocol::ANS_END, code);

	return errorCode;
}

int ClientCommandHandler::deleteArticle(int groupIndex, int articleIndex) throw (ConnectionClosedException){
		int groupId = getGroupId(groupIndex);
		int articleId = getArticleId(articleIndex);

		messageHandler.sendCode(Protocol::COM_DELETE_ART);
		messageHandler.sendIntParameter(groupId);
		messageHandler.sendIntParameter(articleId);
		messageHandler.sendCode(Protocol::COM_END);

		int errorCode = 0;
	
		int code = messageHandler.recvCode();
		checkCode("Delete article", Protocol::ANS_DELETE_ART, code);
		code = messageHandler.recvCode();
		if (code != Protocol::ANS_ACK) {
			checkCondition(code == Protocol::ANS_NAK, "Create group",
					"Did not receive ANS_ACK or ANS_NAK");
			errorCode = messageHandler.recvCode();
		}
		code = messageHandler.recvCode();
		checkCode("Delete article", Protocol::ANS_END, code);
	
		return errorCode;
}

vector<string> ClientCommandHandler::getArticle(int groupIndex, int articleIndex) throw (ConnectionClosedException){
	int groupId = getGroupId(groupIndex);
	int articleId = getArticleId(articleIndex);
	
	messageHandler.sendCode(Protocol::COM_GET_ART);
	messageHandler.sendIntParameter(groupId);
	messageHandler.sendIntParameter(articleId);
	messageHandler.sendCode(Protocol::COM_END);	

	vector<string> result;

	int code = messageHandler.recvCode();
	checkCode("Get article", Protocol::ANS_GET_ART, code);
	code = messageHandler.recvCode();
	if (code != Protocol::ANS_ACK) {
		checkCondition(code == Protocol::ANS_NAK, "Create group",
				"Did not receive ANS_ACK or ANS_NAK");
		result = vector<string>();
//		result.push_back(static_cast<string>(messageHandler.recvCode()));
		result.push_back("");//TODO!!!!!
	} else {
		result = vector<string>();
		result.push_back(messageHandler.recvStringParameter());
		result.push_back(messageHandler.recvStringParameter());
		result.push_back(messageHandler.recvStringParameter());
	}
	code = messageHandler.recvCode();
	checkCode("Delete article", Protocol::ANS_END, code);
	
	return result;
}
int ClientCommandHandler::getGroupId(uint groupIndex){
	return (groupIndex < groupIds.size()) ? groupIds[groupIndex]
				: NE_GROUP_ID;
}

int ClientCommandHandler::getArticleId(uint articleIndex){
	return (articleIndex < articleIds.size()) ? articleIds[articleIndex]
			: NE_ART_ID;
}

void ClientCommandHandler::checkCode(string method, int expectedCode, int code) throw(ProtocolViolationException){
	if (code != expectedCode) {
		throw ProtocolViolationException(method, expectedCode, code);
		
	}
}

void ClientCommandHandler::checkCondition(bool condition, string method, string message) throw(ProtocolViolationException){
	if (!condition) {
	throw new ProtocolViolationException(method, message);
	
	}
}