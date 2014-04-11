#ifndef CLIENT_H
#define CLIENT_H

#include "client_command_handler.h"
#include <vector>
#include <string>
#include "command.h"

class Client{
public:
	Client(Command&);
	void run();
private:
	Command com;
	std::vector<std::string> executeCommand(std::string& input);
};
#endif
