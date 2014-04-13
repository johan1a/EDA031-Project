#include <iostream>
#include <string>
#include "message_handler.h"
#include "connection.h"
#include "exception/connection_closed_exception.h"
#include "protocol.h"
#include "exception/protocol_violation_exception.h"

using namespace std;

MessageHandler::MessageHandler(){}

/**
 * Create a message handler.
 * 
 * @param conn
 *            The connection to use messages
 */
MessageHandler::MessageHandler(const Connection& conn) {
	this->conn = conn;
}

void MessageHandler::changeConnection(const Connection& conn) {
	this->conn = conn;
}

/**
 * Transmit a code (a constant from the Protocol class).
 * 
 * @param code
 *            The code to transmit.
 * @throws ConnectionClosedException
 *             If the server died
 */
void MessageHandler::sendCode(int code) {
	sendByte(code);
}

/**
 * Transmit an int value, according to the protocol.
 * 
 * @param value
 *            The value to transmit
 * @throws ConnectionClosedException
 *             If the server died
 */
void MessageHandler::sendInt(int value) {
	sendByte((value >> 24) & 0xFF);
	sendByte((value >> 16) & 0xFF);
	sendByte((value >> 8) & 0xFF);
	sendByte(value & 0xFF);
}

/**
 * Transmit an int parameter, according to the protocol.
 * 
 * @param value
 *            The parameter to transmit
 * @throws ConnectionClosedException
 *             If the server died
 */
void MessageHandler::sendIntParameter(int param) {
	sendCode(Protocol::PAR_NUM);
	sendInt(param);
}

/**
 * Transmit a string parameter, according to the protocol.
 * 
 * @param value
 *            The parameter to transmit
 * @throws ConnectionClosedException
 *             If the server died
 */
void MessageHandler::sendStringParameter(const string& param) {
	sendCode(Protocol::PAR_STRING);
	sendInt(param.length());
	for (unsigned int i = 0; i < param.length(); i++) {
		sendByte(param[i]);
	}
}

/**
 * Receive a command code or an error code from the server.
 * 
 * @return The code
 * @throws ConnectionClosedException
 *             If the server died
 */
int MessageHandler::recvCode() {
	int code = recvByte();
	return code;
}

/**
 * Receive an int value from the server.
 * 
 * @return The int value
 * @throws ConnectionClosedException
 *             If the server died
 */
int MessageHandler::recvInt() {
	int b1 = recvByte();
	int b2 = recvByte();
	int b3 = recvByte();
	int b4 = recvByte();

	return b1 << 24 | b2 << 16 | b3 << 8 | b4;
}

/**
 * Receive an int parameter from the server.
 * 
 * @return The parameter value
 * @throws ConnectionClosedException
 *             If the server died
 */
int MessageHandler::recvIntParameter() {
	int code = recvCode();
	if (code != Protocol::PAR_NUM) {
		throw ProtocolViolationException("Receive numeric parameter", Protocol::PAR_NUM, code);
	}
	return recvInt();
}

/**
 * Receive a string parameter from the server.
 * 
 * @return The parameter value
 * @throws ConnectionClosedException
 *             If the server died
 */
string MessageHandler::recvStringParameter() {
	int code = recvCode();
	if (code != Protocol::PAR_STRING) {
		throw ProtocolViolationException("Receive string parameter", Protocol::PAR_STRING, code);
	}
	int n = recvInt();
	if (n < 0) {
		throw ProtocolViolationException("Receive string parameter", "Number of characters < 0");
	}
	string result = "";
	for (int i = 1; i <= n; i++) {
		char ch = conn.read();
		result += ch;
	}
	return result;
}

int MessageHandler::recvByte() {
	int code;
	try{
		code = conn.read();
	} catch(...){
		throw ConnectionClosedException();
	}
	return code;
}

void MessageHandler::sendByte(int code) {
	try{
		conn.write(static_cast<char>(code));
	} catch(...){
		throw ConnectionClosedException();
	}
}

