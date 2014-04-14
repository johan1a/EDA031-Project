// ------------------------------------------------------------------
//
//				  ListSyntaxException header file
//
// A ListSyntaxException is thrown when the user input syntax for 
// listing newsgroups or articles is not valid or is out of range
//
//
// ------------------------------------------------------------------

#ifndef LIST_SYNTAX_EXCEPTION_H
#define LIST_SYNTAX_EXCEPTION_H
#include "syntax_exception.h"
#include <string>
class ListSyntaxException : public SyntaxException {
public:
	ListSyntaxException() {msg = "Usage: [list | list <News Group ID>]";}
};
#endif
