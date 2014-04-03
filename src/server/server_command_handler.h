#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

#include "database.h"
#include "../common/message_handler.h"

class ServerCommandHandler {
public:
	ServerCommandHandler(MessageHandler, Database);
	void newMessage(); //throws ConnectionClosedException, ProtocolViolationException
private:
	void listGroups();
	void createGroup();
	void deleteGroup();
	void listArticles();
	void createArticle();
	void deleteArticle();
	void getArticle();
	void checkEnd();

	MessageHandler msgH;
	Database db;
};

#endif
