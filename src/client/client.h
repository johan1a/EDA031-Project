#ifndef CLIENT_H
#define CLIENT_H

#include "client_command_handler.h"
#include <vector>
#include <string>

class Client{
public:
	Client();
	void run();
private:
	ClientCommandHandler cmdHandler;
	std::vector<std::string> executeCommand(std::string& input);
};
#endif