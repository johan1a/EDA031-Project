// ------------------------------------------------------------------
//
//				  ReadSyntaxException header file
//
// A ReadSyntaxException is thrown when the user input syntax for 
// reading an article is not valid or is out of range
//
//
// ------------------------------------------------------------------

#ifndef READ_SYNTAX_EXCEPTION_H
#define READ_SYNTAX_EXCEPTION_H
#include "syntax_exception.h"
#include <string>
struct ReadSyntaxException : public SyntaxException{
	ReadSyntaxException() {msg = "Usage: read <News Group ID> <Article ID>";}
};
#endif
