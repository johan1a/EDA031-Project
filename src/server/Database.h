#ifndef DATABASE_H
#define DATABASE_H
#include <string>



class Database{
public:

	virtual std::string& listNewsGroup(const std::string& ngName);
	virtual std::string& createNewsGroup(const std::string& ngName);
	virtual std::string& deleteNewsGroup(const std::string& ngName);
	virtual std::string& listArticlesFor(const std::string& ngName);
	virtual std::string& readArticle(const std::string& articleName, const std::string& ngName);
	virtual std::string& writeArticle(const std::string& articleName, const std::string& ngName);
	virtual std::string& deleteArticle(const std::string& articleName, const std::string& ngName);

};

#endif
