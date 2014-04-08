#ifndef CACHE_DATABASE_H
#define CACHE_DATABASE_H

#include <map>
#include "database.h"
#include "cache_database.h"

class CacheDatabase : public Database {
public:
	CacheDatabase();
	void createNewsGroup(const std::string& groupName);
	void deleteArticle(int groupID, int articleID);
	void deleteNewsGroup(int groupID);
	std::vector<Article> listArticlesFor(int groupID) const;
	std::vector<NewsGroup> listNewsGroups() const;
	Article readArticle(int groupID, int articleID) const;
	void writeArticle(int groupID, Article& article);
private:
	std::map<int, NewsGroup> database;
};

#endif
