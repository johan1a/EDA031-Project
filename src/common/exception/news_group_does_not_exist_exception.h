#ifndef NEWS_GROUP_DOES_NOT_EXIST_EXCEPTION_H
#define NEWS_GROUP_DOES_NOT_EXIST_EXCEPTION_H
#include <string>
struct NewsGroupDoesNotExistException {
	std::string msg = "The news group does not exist.";
};

#endif
