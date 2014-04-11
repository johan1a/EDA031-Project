#ifndef COMMAND_H
#define COMMAND_H

#include <vector>
#include <string>
#include "client_command_handler.h"

class Command{
	public:
		Command();
		Command(ClientCommandHandler&);
		std::vector<std::string> list(std::vector<std::string>&);
		std::vector<std::string> read(std::vector<std::string>&);
		void create(std::vector<std::string>&);
		void del(std::vector<std::string>&);
	private:
		ClientCommandHandler cmdHandler;
};

#endif
