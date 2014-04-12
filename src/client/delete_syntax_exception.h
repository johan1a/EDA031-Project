#ifndef DELETE_SYNTAX_EXCEPTION_H
#define DELETE_SYNTAX_EXCEPTION_H
#include "syntax_exception.h"
#include <string>
class DeleteSyntaxException : public SyntaxException {
public:
	DeleteSyntaxException() {msg ="Usage: delete [group <News Group ID> | article <News Group ID> <Article ID>]";}
};
#endif
