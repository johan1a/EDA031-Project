#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H
#include <string>
#include <vector>
//#include "message_handler.h"

class ClientCommandHandler{
public:
	ClientCommandHandler();
	std::string listGroups();
	int createGroup(std::string title);
	int deleteGroup(int groupIndex);
	std::string listArticles(int groupIndex);
	int createArticle(int groupIndex, std::string title, std::string author, std::string text);
	int deleteArticle(int groupIndex, int articleIndex);
	std::string getArticle(int groupIndex, int articleIndex);

private:
	//MessageHandler messageHandler;
	std::vector<int> groupIds;
	std::vector<int> articleIds;
	const int NE_GROUP_ID = 999999; // These id's do not exist
	const int NE_ART_ID = 888888;

	int getGroupId(int groupIndex);
	int getArticleId(int articleIndex);
	void checkCode(std::string method, int expectedCode, int code);
	void checkCondition(bool condition, std::string method, std::string message);

};
#endif