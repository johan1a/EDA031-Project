#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H

#include <string>
#include <vector>
#include "../common/message_handler.h"
#include "../common/connection.h"
#include "../common/connection_closed_exception.h"
#include "../common/protocol_violation_exception.h"

class ClientCommandHandler{
public:
	ClientCommandHandler();
	ClientCommandHandler(Connection &conn);
	std::vector<std::string> listGroups() throw(ConnectionClosedException);
	int createGroup(std::string title) throw(ConnectionClosedException);
	int deleteGroup(int groupIndex) throw (ConnectionClosedException,
			ProtocolViolationException );
	std::vector<std::string> listArticles(int groupIndex) throw ( ConnectionClosedException);
	int createArticle(int groupIndex, std::string title, std::string author, std::string text) throw (ConnectionClosedException,
			ProtocolViolationException);
	int deleteArticle(int groupIndex, int articleIndex) throw (ConnectionClosedException);
	std::vector<std::string> getArticle(int groupIndex, int articleIndex) throw (ConnectionClosedException);

private:
	MessageHandler messageHandler;
	std::vector<int> groupIds;
	std::vector<int> articleIds;
	const int NE_GROUP_ID = 999999; // These id's do not exist
	const int NE_ART_ID = 888888;

	int getGroupId(unsigned int groupIndex);
	int getArticleId(unsigned int articleIndex);
	void checkCode(std::string method, int expectedCode, int code) throw(ProtocolViolationException);
	void checkCondition(bool condition, std::string method, std::string message) throw (ProtocolViolationException);
};
#endif
