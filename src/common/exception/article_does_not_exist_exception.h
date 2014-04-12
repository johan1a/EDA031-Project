#ifndef ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
#define ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
#include <string>

struct ArticleDoesNotExistException {
	std::string msg = "The article does not exist.";
};

#endif
