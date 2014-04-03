#include <string>
#include <vector>
#include "../common/protocol_violation_exception.h"
#include "news_group_does_not_exist_exception.h"
#include "news_group_already_exists_exception.h"
#include "article_does_not_exist_exception.h"
#include "server_command_handler.h"
#include "../common/protocol.h"
#include "database.h"

using namespace std;

ServerCommandHandler::ServerCommandHandler(MessageHandler msgHandler, Database database) : msgH(msgHandler), db(database) {}

void ServerCommandHandler::newMessage() {
	uint cmd = msgH.recvCode();
	switch (cmd) {
		case Protocol::COM_LIST_NG:
			listGroups();
			break;
		case Protocol::COM_CREATE_NG:
			createGroup();
			break;
		case Protocol::COM_DELETE_NG:
			deleteGroup();
			break;
		case Protocol::COM_LIST_ART:
			listArticles();
			break;
		case Protocol::COM_CREATE_ART:
			createArticle();
			break;
		case Protocol::COM_DELETE_ART:
			deleteArticle();
			break;
		case Protocol::COM_GET_ART:
			getArticle();
			break;
		default:
			throw ProtocolViolationException("", "");
	}
	msgH.sendCode(Protocol::ANS_END);
}

void ServerCommandHandler::listGroups() {
	checkEnd();
	msgH.sendCode(Protocol::ANS_LIST_NG);
	vector<NewsGroup> newsGroups = db.listNewsGroups();
	msgH.sendIntParameter(newsGroups.size());
	for (auto it = newsGroups.begin(); it != newsGroups.end(); ++it) {
		msgH.sendIntParameter(it->id);
		msgH.sendStringParameter(it->name);
	}
}

void ServerCommandHandler::createGroup() {
	string title = msgH.recvStringParameter();
	checkEnd();
	msgH.sendCode(Protocol::ANS_CREATE_NG);
	try {
		db.createNewsGroup(title);
		msgH.sendCode(Protocol::ANS_ACK);
	} catch (NewsGroupAlreadyExistsException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_ALREADY_EXISTS);
	}
}

void ServerCommandHandler::deleteGroup() {
	int ngi = msgH.recvIntParameter();
	checkEnd();
	msgH.sendCode(Protocol::ANS_DELETE_NG);
	try {
		db.deleteNewsGroup(ngi);
		msgH.sendCode(Protocol::ANS_ACK);
	} catch (NewsGroupDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerCommandHandler::listArticles() {
	int ngi = msgH.recvIntParameter();
	checkEnd();
	msgH.sendCode(Protocol::ANS_LIST_ART);
	try {
		vector<Article> articles = db.listArticlesFor(ngi);
		msgH.sendCode(Protocol::ANS_ACK);
		for(auto it = articles.begin(); it != articles.end(); ++it) {
			msgH.sendIntParameter(it->id);
			msgH.sendStringParameter(it->title);
		}
	} catch (NewsGroupDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerCommandHandler::createArticle() {
	int ngi = msgH.recvIntParameter();
	string title = msgH.recvStringParameter();
	string author = msgH.recvStringParameter();
	string text = msgH.recvStringParameter();
	checkEnd();
	Article art(title, author, text);
	try {
		db.writeArticle(ngi, art);
		msgH.sendCode(Protocol::ANS_ACK);
	} catch (NewsGroupDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	}
}

void ServerCommandHandler::deleteArticle() {
	int ngi = msgH.recvIntParameter();
	int arti = msgH.recvIntParameter();
	checkEnd();
	try {
		db.deleteArticle(ngi, arti);
		msgH.sendCode(Protocol::ANS_ACK);
	} catch (NewsGroupDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	} catch (ArticleDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
	}
}

void ServerCommandHandler::getArticle() {
	int ngi = msgH.recvIntParameter();
	int arti = msgH.recvIntParameter();
	checkEnd();
	try {
		Article art = db.readArticle(ngi, arti);
		msgH.sendCode(Protocol::ANS_ACK);
		msgH.sendStringParameter(art.title);
		msgH.sendStringParameter(art.author);
		msgH.sendStringParameter(art.text);
	} catch (NewsGroupDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_NG_DOES_NOT_EXIST);
	} catch (ArticleDoesNotExistException& e) {
		msgH.sendCode(Protocol::ANS_NAK);
		msgH.sendCode(Protocol::ERR_ART_DOES_NOT_EXIST);
	}
}

void ServerCommandHandler::checkEnd() {
	if (msgH.recvCode() != Protocol::COM_END) {
		throw ProtocolViolationException("", "");
	}
}
