#ifndef NEWS_CLIENT_H
#define NEWS_CLIENT_H

#include "client_command_handler.h"
#include <vector>
#include <string>
#include "user_input_handler.h"

class NewsClient{
public:
	NewsClient(UserInputHandler&);
	void run();
private:
	UserInputHandler handler;
	std::vector<std::string> executeCommand(std::vector<std::string>);
	const std::string AVAILABLE_COMMANDS = "Available commands: \n"
	"list\n"
	"list <newsgroup ID>\n"
	"read <newsgroup ID> <article ID>\n"
	"create group\n"
	"create article <newsgroup ID>\n"
	"delete group <newsgroup ID>\n"
	"delete article <newsgroup ID> <article ID>\n"
	"exit";
};
#endif
