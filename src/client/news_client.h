#ifndef NEWS_CLIENT_H
#define NEWS_CLIENT_H

#include "client_command_handler.h"
#include <vector>
#include <string>
#include "user_input_handler.h"

/* The client that throughputs the users valid commands to the server, via the shared connection, established in the very beginning */
class NewsClient{
public:
	/* Creates a client with a dedicated UserInputHandler 
	*/
	NewsClient(UserInputHandler&);

	/* Sets up the entire interface between the client and the user. Maintains the connnection and handles the commands from the user 
	*/ 
	void run();
private:
	/* The user input handler that handles the input from the user 
	*/
	UserInputHandler handler;

	/* Executes the commands from the user. Returns a list of group or articles if the execution was successful 
	*/
	std::vector<std::string> executeCommand(std::vector<std::string>);

	/* A list of valid commands 
	*/
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
