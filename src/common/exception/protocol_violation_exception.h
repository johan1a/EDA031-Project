#include <string>

#ifndef PROTOCOL_VIOLATION_EXCEPTION_H
#define PROTOCOL_VIOLATION_EXCEPTION_H


struct ProtocolViolationException {
	std::string msg;
	std::string err;
	int protMsg;
	int codeNbr;
	ProtocolViolationException(std::string m, int prot, int code):
		msg(m), protMsg(prot), codeNbr(code) {}

	ProtocolViolationException(std::string m, std::string em):
		msg(m), err(em) {}
};
#endif
