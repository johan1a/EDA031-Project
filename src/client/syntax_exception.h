#include <string>

#ifndef SYNTAX_EXCEPTION_H
#define SYNTAX_EXCEPTION_H


struct SyntaxException {
	std::string msg;

	SyntaxException(std::string m):
		msg(m) {}
};
#endif
