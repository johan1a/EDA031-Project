#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>



class Database{
public:

	virtual std::vector<std::pair<int, std::string> >& listNewsGroups() const;
	virtual bool createNewsGroup(const std::string& ngName);
	virtual std::string& deleteNewsGroup(const std::string& ngName);
	virtual std::string& listArticlesFor(const std::string& ngName);
	virtual std::string& readArticle(const std::string& articleName, const std::string& ngName);
	virtual std::string& writeArticle(const std::string& articleName, const std::string& ngName);
	virtual std::string& deleteArticle(const std::string& articleName, const std::string& ngName);

};

#endif
