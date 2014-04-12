#ifndef SYNTAX_EXCEPTION_H
#define SYNTAX_EXCEPTION_H
#include <string>

class SyntaxException{
public:
	std::string msg;
	SyntaxException() = default;
};
#endif
