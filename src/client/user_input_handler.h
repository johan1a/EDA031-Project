#ifndef USER_INPUT_HANDLER_H
#define USER_INPUT_HANDLER_H

#include <vector>
#include <string>
#include "../common/exception/syntax_exception.h"
#include "../common/exception/delete_syntax_exception.h"
#include "../common/exception/list_syntax_exception.h"
#include "../common/exception/create_syntax_exception.h"
#include "../common/exception/read_syntax_exception.h"
#include "../common/exception/article_does_not_exist_exception.h"
#include "../common/exception/news_group_does_not_exist_exception.h"
#include "client_command_handler.h"

/**
 * UserInputHandler is the first hand class that handles the commands from the terminal, input by the user. 
 */
class UserInputHandler{
	public:
		/* Creates an empty UserInputHandler 
		*/
		UserInputHandler();

		/* Creates an UserInputHandler with a dedicated ClientCommandHandler 
		*/
		UserInputHandler(ClientCommandHandler&);
		
		/* Calls this function if the first token in the user input is "list" 
		Throws ListSyntaxException if the user input syntax for list is not valid or is out of range 
		Throws NewsGroupDoesNotExistException if the newsgroup does not exist
		Throws ArticleDoesNotExistException if an article does not exist
		Throws ConnectionClosedException if the server closes the connection. 
   	    Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
		*/
		std::vector<std::string> list(std::vector<std::string>&) throw (ListSyntaxException, NewsGroupDoesNotExistException, ArticleDoesNotExistException, ConnectionClosedException, ProtocolViolationException);

		/* Calls this function if the first token in the user input is "read" 
		Throws NewsGroupDoesNotExistException if the newsgroup does not exist
		Throws ArticleDoesNotExistException if an article does not exist 
		Throws ReadSyntaxException if the user input syntax for read is not valid or is out of range
		Throws ConnectionClosedException if the server closes the connection. 
   	    Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
		*/
		std::vector<std::string> read(std::vector<std::string>&) throw (NewsGroupDoesNotExistException, ArticleDoesNotExistException, ReadSyntaxException, ConnectionClosedException, ProtocolViolationException);
		
		/* Calls this function if the first token in the user input is "create" 
		Throws CreateSyntaxException if the user input syntax for create is not valid or is out of range
		Throws NewsGroupDoesNotExistException if the newsgroup does not exist
		Throws ConnectionClosedException if the server closes the connection. 
   	    Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
		*/
		void create(std::vector<std::string>&)  throw (CreateSyntaxException, NewsGroupDoesNotExistException, ConnectionClosedException, ProtocolViolationException);

		/* Calls this function if the first token in the user input is "delete" 
		Throws NewsGroupDoesNotExistException if the newsgroup does not exist
		Throws ArticleDoesNotExistException if an article does not exist 
		Throws DeleteSyntaxException if the user input syntax for delete is not valid or is out of range
		Throws ConnectionClosedException if the server closes the connection. 
   	    Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
		*/	
		void del(std::vector<std::string>&) throw (NewsGroupDoesNotExistException, ArticleDoesNotExistException, DeleteSyntaxException, ConnectionClosedException, ProtocolViolationException);
	private:
		/* The client command handler that handles the commands from the user more precisely 
		*/
		ClientCommandHandler cmdHandler;
};

#endif
