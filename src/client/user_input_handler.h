#ifndef USER_INPUT_HANDLER_H
#define USER_INPUT_HANDLER_H

#include <vector>
#include <string>
#include "../common/exception/syntax_exception.h"
#include "../common/exception/delete_syntax_exception.h"
#include "../common/exception/list_syntax_exception.h"
#include "../common/exception/create_syntax_exception.h"
#include "../common/exception/read_syntax_exception.h"
#include "../common/exception/article_does_not_exist_exception.h"
#include "../common/exception/news_group_does_not_exist_exception.h"
#include "client_command_handler.h"

class UserInputHandler{
	public:
		UserInputHandler();
		UserInputHandler(ClientCommandHandler&);
		std::vector<std::string> list(std::vector<std::string>&) throw (ListSyntaxException, NewsGroupDoesNotExistException, ArticleDoesNotExistException );
		std::vector<std::string> read(std::vector<std::string>&) throw (ArticleDoesNotExistException, ReadSyntaxException);
		void create(std::vector<std::string>&)  throw (CreateSyntaxException, CreateSyntaxException);
		void del(std::vector<std::string>&) throw (NewsGroupDoesNotExistException, ArticleDoesNotExistException, DeleteSyntaxException);
	private:
		ClientCommandHandler cmdHandler;
};

#endif
