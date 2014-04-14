// ------------------------------------------------------------------
//
//				  DeleteSyntaxException header file
//
// A DeleteSyntaxException is thrown when the user input syntax for 
// deleting a newsgroup or an article is not valid or is out of range
//
//
// ------------------------------------------------------------------

#ifndef DELETE_SYNTAX_EXCEPTION_H
#define DELETE_SYNTAX_EXCEPTION_H
#include "syntax_exception.h"
#include <string>
class DeleteSyntaxException : public SyntaxException {
public:
	DeleteSyntaxException() {msg ="Usage: delete [group <News Group ID> | article <News Group ID> <Article ID>]";}
};
#endif
