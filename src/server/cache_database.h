#ifndef CACHE_DATABASE_H
#define CACHE_DATABASE_H

#include <map>
#include "database.h"

class CacheDatabase : public Database {
public:
	CacheDatabase();
	std::vector<NewsGroup> listNewsGroups() const;
	void createNewsGroup(const std::string&);
	void deleteNewsGroup(int);
	std::vector<Article> listArticlesFor(int) const;
	Article readArticle(int, int) const;
	void writeArticle(int, Article&);
	void deleteArticle(int, int);
private:
	std::map<int, NewsGroup> database;
};

#endif
