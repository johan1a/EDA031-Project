#ifndef CACHE_DATABASE_H
#define CACHE_DATABASE_H

#include <map>
#include "database.h"
#include "cache_database.h"

class CacheDatabase : public Database {
public:
	CacheDatabase();
	std::vector<NewsGroup> listNewsGroups() const;
	void createNewsGroup(const std::string& groupName);
	void deleteNewsGroup(int groupID);
	std::vector<Article> listArticlesFor(int groupID) const;
	Article readArticle(int groupID, int articleID) const;
	void writeArticle(int groupID, Article& article);
	void deleteArticle(int groupID, int articleID);
private:
	std::map<int, NewsGroup> database;
};

#endif
