#ifndef MESSAGE_HANDLER_H
#define MESSAGE_HANDLER_H

#include <iostream>
#include <string>
#include "connection.h"

/**
 * Message handler is the low-level message handler for messages to/from the
 * server. It handles transmission/reception of low-level message units.
 */

class MessageHandler {
public:
	MessageHandler();

	/**
	 * Create a message handler.
	 * 
	 * @param conn
	 *            The connection to use messages
	 */
	MessageHandler(const Connection& conn);

	void changeConnection(const Connection& conn);

	/**
	 * Transmit a code (a constant from the Protocol class).
	 * 
	 * @param code
	 *            The code to transmit.
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendCode(int code);

	/**
	 * Transmit an int value, according to the protocol.
	 * 
	 * @param value
	 *            The value to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendInt(int value);
	/**
	 * Transmit an int parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendIntParameter(int param);

	/**
	 * Transmit a string parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendStringParameter(const std::string& param);

	/**
	 * Receive a command code or an error code from the server.
	 * 
	 * @return The code
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvCode();

	/**
	 * Receive an int value from the server.
	 * 
	 * @return The int value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvInt();

	/**
	 * Receive an int parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvIntParameter();

	/**
	 * Receive a string parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	std::string recvStringParameter();

private:
	Connection conn; // the connection
	int recvByte();
	void sendByte(int code);
};

#endif
