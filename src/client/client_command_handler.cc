#include "client_command_handler.h"
#include "../common/protocol.h"
using namespace std;

ClientCommandHandler::ClientCommandHandler(){}

ClientCommandHandler::ClientCommandHandler(MessageHandler& mh): messageHandler(mh) {}

vector<string> ClientCommandHandler::listGroups() throw (ConnectionClosedException, ProtocolViolationException){
	messageHandler.sendCode(Protocol::COM_LIST_NG);
	messageHandler.sendCode(Protocol::COM_END);

	int code = messageHandler.recvCode();
	checkCode("List groups", Protocol::ANS_LIST_NG, code);

	int nbrGroups = messageHandler.recvIntParameter();
	checkCondition(nbrGroups >= 0, "List groups", "Number of groups < 0");
	vector<string> groupNames(nbrGroups);
	for(int i = 0; i < nbrGroups; ++i){
		groupNames[i] = to_string(messageHandler.recvIntParameter()) + ". ";
		groupNames[i] = groupNames[i] + messageHandler.recvStringParameter();
	}
	code = messageHandler.recvCode();
	checkCode("List groups", Protocol::ANS_END, code);
	return groupNames;	
}

int ClientCommandHandler::createGroup(string title) throw(ConnectionClosedException, ProtocolViolationException) {		
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

int ClientCommandHandler::deleteGroup(int groupId)  throw (ConnectionClosedException,
			ProtocolViolationException){

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

vector<string> ClientCommandHandler::listArticles(int groupId) throw (ConnectionClosedException, NewsGroupDoesNotExistException, ArticleDoesNotExistException, ProtocolViolationException){
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
		messageHandler.recvCode(); // hopefully ANS_NAK, not checked
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			throw NewsGroupDoesNotExistException();
		} else {
			throw ArticleDoesNotExistException();
		}
		return vector<string>();
	}
	int nbrArticles = messageHandler.recvIntParameter();
	checkCondition(nbrArticles >= 0, "List articles",
			"Number of groups < 0");
	vector<string> articleNames(nbrArticles);
	for (int i = 0; i < nbrArticles; i++) {
		articleNames[i] = to_string(messageHandler.recvIntParameter()) + ". ";
		articleNames[i] = articleNames[i] + messageHandler.recvStringParameter();

	}
	code = messageHandler.recvCode();
	checkCode("List articles", Protocol::ANS_END, code);

	return articleNames;
}

int ClientCommandHandler::createArticle(int groupId, string title, string author, string text) throw (ConnectionClosedException,
			ProtocolViolationException){
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

int ClientCommandHandler::deleteArticle(int groupId, int articleId) throw (ConnectionClosedException, ProtocolViolationException){

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

vector<string> ClientCommandHandler::getArticle(int groupId, int articleId) throw (ConnectionClosedException, NewsGroupDoesNotExistException, ArticleDoesNotExistException, ProtocolViolationException){
	
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
		code = messageHandler.recvCode();
		checkCode("Delete article", Protocol::ANS_END, messageHandler.recvCode());
		if (code == Protocol::ERR_NG_DOES_NOT_EXIST) {
			throw NewsGroupDoesNotExistException();
		} else {
			throw ArticleDoesNotExistException();
		}
	} else {
		result = vector<string>();
		result.push_back("Title: " + messageHandler.recvStringParameter());
		result.push_back("Author: " + messageHandler.recvStringParameter());
		result.push_back("Text: " + messageHandler.recvStringParameter());
	}
	code = messageHandler.recvCode();
	checkCode("Delete article", Protocol::ANS_END, code);
	
	return result;
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
