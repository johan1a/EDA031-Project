#ifndef CREATE_SYNTAX_EXCEPTION_H
#define CREATE_SYNTAX_EXCEPTION_H
#include "syntax_exception.h"
#include <string>
class CreateSyntaxException : public SyntaxException{
public:
	CreateSyntaxException() {msg ="Usage: create [group | article]";}
};
#endif
