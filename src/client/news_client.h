#ifndef NEWS_CLIENT_H
#define NEWS_CLIENT_H

#include "client_command_handler.h"
#include <vector>
#include <string>
#include "command.h"

class NewsClient{
public:
	NewsClient(Command&);
	void run();
private:
	Command com;
	std::vector<std::string> executeCommand(std::string& input);
};
#endif
