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
	std::string availableCommands;
	UserInputHandler handler;
	std::vector<std::string> executeCommand(std::vector<std::string>);
};
#endif
