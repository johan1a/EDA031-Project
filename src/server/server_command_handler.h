#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

using namespace std;

class ServerCommandHandler {
public:
	ServerCommandHandler(MessageHandler&);
	void newMessage();
private:
	void listGroups();
	void createGroup();
	void deleteGroup();
	void listArticles();
	void createArticle();
	void deleteArticle();
	void getArticle();
	void checkEnd();
	
	Database db;
	MessageHandler& msgH;
}

#endif
