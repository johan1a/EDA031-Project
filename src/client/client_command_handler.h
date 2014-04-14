#ifndef CLIENTCOMMANDHANDLER_H
#define CLIENTCOMMANDHANDLER_H

#include <string>
#include <vector>
#include "../common/message_handler.h"
#include "../common/exception/connection_closed_exception.h"
#include "../common/exception/protocol_violation_exception.h"
#include "../common/exception/article_does_not_exist_exception.h"
#include "../common/exception/news_group_does_not_exist_exception.h"

/**
 * ClientCommandHandler that handles the existing commands from the client. The difference between this class and the UserInputHandler is that 
 * ClientCommandHandler handles the commands more precisely, before they are transmitted to the server.
 */

class ClientCommandHandler{
public:
	/* Creates an empty ClientCommandHandler 
	*/
	ClientCommandHandler();

	/* Creates a ClientCommandHandler with a dedicated MessageHandler 
	*/
	ClientCommandHandler(MessageHandler& mh);

	/* Lists all the newsgroups. 
	Throws ConnectionClosedException if the server closes the connection. 
	Throws ProtocolViolationException if the communication between the client and the server does not follow protocol, defined in protocol.h 
	*/
	std::vector<std::string> listGroups() throw(ConnectionClosedException, ProtocolViolationException);

	/* Creates a newsgroup with the title 'title'. 
	Throws ConnectionClosedException if the server closes the connection. 
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	int createGroup(std::string title) throw(ConnectionClosedException, ProtocolViolationException);

	/* Deletes the newsgroup with group ID 'groupIndex'. 
	Throws ConnectionClosedException if the server closes the connection. 
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	int deleteGroup(int groupIndex) throw (ConnectionClosedException, ProtocolViolationException);

	/* Lists all the articles in the newsgroup with the group ID 'groupIndex'. 
	Throws ConnectionClosedException if the server closes the connection. 
	Throws NewsGroupDoesNotExistexception if the newsgroup ID number input by the the user does not exist.
	Throws ArticleDoesNotExistexception if the newsgroup is empty.
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	std::vector<std::string> listArticles(int groupIndex) throw (ConnectionClosedException, NewsGroupDoesNotExistException, ArticleDoesNotExistException, ProtocolViolationException);

	/* Creates an article with the title 'title', author 'author', and text 'text' in the newsgroup with the group ID groupIndex. 
	Throws ConnectionClosedException if the server closes the connection. 
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	int createArticle(int groupIndex, std::string title, std::string author, std::string text) throw (ConnectionClosedException, ProtocolViolationException);

	/* Deletes an article with the the article ID 'articleIndex', in a newsgroup with the group ID 'groupIndex'
	Throws ConnectionClosedException if the server closes the connection. 
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	int deleteArticle(int groupIndex, int articleIndex) throw (ConnectionClosedException, ProtocolViolationException);

	/* Retrieves an article with the article ID 'articleIndex' from the newsgroup with the group ID 'groupIndex'
	Throws ConnectionClosedException if the server closes the connection. 
	Throws NewsGroupDoesNotExistexception if the newsgroup ID number input by the the user does not exist.
	Throws ArticleDoesNotExistexception if the article ID does not exist in the newsgroup with the corresponding group ID.
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	std::vector<std::string> getArticle(int groupIndex, int articleIndex) throw (ConnectionClosedException, NewsGroupDoesNotExistException, ArticleDoesNotExistException, ProtocolViolationException);

private:
	/* The message handler that sends and receives the commands and the results respectively to and from the server 
	*/
	MessageHandler messageHandler;

	/* Checks if the received code 'code' from the server matches with the expected answer 'expectedCode' 
    Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	void checkCode(std::string method, int expectedCode, int code) throw (ProtocolViolationException);

	/* Checks the condition of received code. If the condiditon is not fulfilled an exception is thrown and prints a message about the command (method) that 
	   was supposed be fulfilled and what went wrong 
	Throws ProtocolViolationException if the communication between the client and the server does not follow the protocol, defined in protocol.h 
	*/
	void checkCondition(bool condition, std::string method, std::string message) throw (ProtocolViolationException);
};
#endif
