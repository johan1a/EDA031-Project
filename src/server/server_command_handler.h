#ifndef SERVER_COMMAND_HANDLER_H
#define SERVER_COMMAND_HANDLER_H

#include "database.h"
#include "../common/message_handler.h"

class ServerCommandHandler {
public:
	/* Creates an instance of this class with knowledge of a Message Handler 
	   (from the Common folder) and a database.
	*/
	ServerCommandHandler(MessageHandler&, Database&);

	/* Grabs the message from the message handler and determins the type of this message. Each type has a corresponding 
	   private method in this class which is invoked if the aquired message is valid.
	Throws an instance of ConnectionClosedException.h if the Client disconnected.
	Throws an instace of ProtocolViolationException.h if the Client sent a faulty protocol.
	*/
	void newMessage(); //throws ConnectionClosedException, ProtocolViolationException

private:

	/* Invokes the listNewsGroups() method from the database and aquires the information in a vector. Hence after sends this 
	   information to the client using the message handler along with right protocols.
	*/
	void listGroups();

	/* Invokes the createNewsGroup("title") method from the database and sends an ACK protocol 
	   back as confirmation that the job was done. The "title" string is aquired from the message handler.
	Throws an instance of NewsGroupAlreadyExistsException.h if the newsgroup already existed.
	*/
	void createGroup();

	/* Invokes the deleteNewsGroup(id) method from the database and sends an ACK protocol 
	   back as confirmation that the job was done. The int id is aquired from the message handler.
	Throws n instance of NewsGroupDoesNotExistException.h if the newsgroup did'nt exist.
	*/
	void deleteGroup();

	/* Invokes the listArticlesFor(newsgroupId) method from the database and sends an ACK protocol 
	   back as confirmation that the job was done. The information aquired from the database is
	   also sent to the client via the message handler.
	Throws an instance of NewsGroupDoesNotExistException.h if the newsgroupId was not found.
	*/
	void listArticles();

	/* Receives the parameters "title", "id", "author" and "text" from the message handler. This is put together as an instance 
	   of the struct Article which is passed to the writeArticle(id, article) method from the database. 
	   An ACK is sent back to the client as confirmation.  
	Throws an instance of NewsGroupDoesNotExistException.h if the newsgroupId was not found.
	*/
	void createArticle();

	/* Receives the parameters int "newsgroupId" and the Article& art from the message handler. 
	   Then the method deleteArticle(nesgroupId, art) from the database is invoked.
	   An ACK is sent back to the client as confirmation.
	Throws an instance of NewsGroupDoesNotExistException.h if the newsgroupId was not found.
	Throws an instance of ArticleDoesNotExistException.h is the article did'nt exist.
	*/
	void deleteArticle();

	/* Receives the parameters int "newsgroupId" and the Article& art from the message handler. Hence after the method 
	   readArticle(newsgroupId, art) is ivoked and the aquired information is sent to the client via the message handler.
	   An ACK is sent back to the client as confirmation.
	Throws an instance of NewsGroupDoesNotExistException.h if the newsgroupId was not found.
	Throws an instance of ArticleDoesNotExistException.h is the article did'nt exist.
	*/
	void getArticle();

	/* Checks if the next protocol was COM_END.
	Throws an instance of ProtocolViolationException.h if is was'nt.
	*/
	void checkEnd();
	
	/* The message handler that sends and receives the commands and the results respectively to and from the server 
	*/
	MessageHandler& msgH;

	/* The database where the information is stored and retrieved 
	*/
	Database& db;
};

#endif
