// ------------------------------------------------------------------
//
//  		  NewsGroupDoesNotExistException header file
//
// A NewsGroupDoesNotExistException is thrown if the newsgroup ID 
// number input by the the user does not exist.
//
//
// ------------------------------------------------------------------

#ifndef NEWS_GROUP_DOES_NOT_EXIST_EXCEPTION_H
#define NEWS_GROUP_DOES_NOT_EXIST_EXCEPTION_H
#include <string>
struct NewsGroupDoesNotExistException {
	std::string msg = "The news group does not exist.";
};

#endif
