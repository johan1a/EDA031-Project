// ------------------------------------------------------------------
//
//				  	SyntaxException header file
//
// A SyntaxException is a super class to all syntax exceptions. All 
// syntax exceptions should contain a message 'msg' that explains why
// the exception was thrown or why the user input was not valid.
//
//
// ------------------------------------------------------------------

#ifndef SYNTAX_EXCEPTION_H
#define SYNTAX_EXCEPTION_H
#include <string>

class SyntaxException{
public:
	std::string msg;
	SyntaxException() = default;
};
#endif
