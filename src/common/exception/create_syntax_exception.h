// ------------------------------------------------------------------
//
//				  CreateSyntaxException header file
//
// A CreateSyntaxException is thrown when the user input syntax for 
// creating a newsgroup or an article is not valid or is out of range
//
//
// ------------------------------------------------------------------

#ifndef CREATE_SYNTAX_EXCEPTION_H
#define CREATE_SYNTAX_EXCEPTION_H
#include "syntax_exception.h"
#include <string>
class CreateSyntaxException : public SyntaxException{
public:
	CreateSyntaxException() {msg ="Usage: create [group | article]";}
};
#endif
