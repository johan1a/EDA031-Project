#include <string>

#ifndef SERVER_EXCEPTION_H
#define SERVER_EXCEPTION_H


struct ServerException {
	std::string msg;

	ServerException(std::string m):
		msg(m) {}
};
#endif
