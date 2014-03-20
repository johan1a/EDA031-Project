#include <string>
#include <iostream>

/**
 * Message handler is the low-level message handler for messages to/from the
 * server. It handles transmission/reception of low-level message units.
 */

class MessageHandler {
public:

	/**
	 * Create a message handler.
	 * 
	 * @param conn
	 *            The connection to use messages
	 */
	MessageHandler(const Connection& conn);

	/**
	 * Transmit a code (a constant from the Protocol class).
	 * 
	 * @param code
	 *            The code to transmit.
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendCode(int code) throws ConnectionClosedException;

	/**
	 * Transmit an int value, according to the protocol.
	 * 
	 * @param value
	 *            The value to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendInt(int value) throws ConnectionClosedException;
	/**
	 * Transmit an int parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendIntParameter(int param) throws ConnectionClosedException;

	/**
	 * Transmit a string parameter, according to the protocol.
	 * 
	 * @param value
	 *            The parameter to transmit
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	void sendStringParameter(string param) throws ConnectionClosedException;

	/**
	 * Receive a command code or an error code from the server.
	 * 
	 * @return The code
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvCode() throws ConnectionClosedException;

	/**
	 * Receive an int value from the server.
	 * 
	 * @return The int value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvInt() throws ConnectionClosedException;

	/**
	 * Receive an int parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	int recvIntParameter() throws ConnectionClosedException;

	/**
	 * Receive a string parameter from the server.
	 * 
	 * @return The parameter value
	 * @throws ConnectionClosedException
	 *             If the server died
	 */
	string recvStringParameter() throws ConnectionClosedException;

private:
	Connection* conn; // the connection
	int recvByte() throws ConnectionClosedException;
	void sendByte(int code) throws ConnectionClosedException;
};
