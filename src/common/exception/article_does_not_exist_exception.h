// ------------------------------------------------------------------
//
//				  ArticleDoesNotExistException header file
//
// A ArticleDoesNotExistException is thrown if an article ID does not 
// exist in a newsgroup with the corresponding group ID.
//
//
// ------------------------------------------------------------------

#ifndef ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
#define ARTICLE_DOES_NOT_EXIST_EXCEPTION_H
#include <string>

struct ArticleDoesNotExistException {
	std::string msg = "The article does not exist.";
};

#endif
