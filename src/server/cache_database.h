#ifndef CACHE_DATABASE_H
#define CACHE_DATABASE_H

#include <map>
#include "database.h"
#include "cache_database.h"

/* A news group database that stores all data temporarily;
	everything is deleted when the program exits.
	This class derives from the abstract base class Database. 
	See file database.h for documentation of the overridden methods. */
class CacheDatabase : public Database {
public:
	CacheDatabase();
	void createNewsGroup(const std::string& groupName) throw (NewsGroupAlreadyExistsException) override;
	void deleteArticle(int groupID, int articleID) throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException) override;
	void deleteNewsGroup(int groupID) throw (NewsGroupDoesNotExistException) override;
	std::vector<Article> listArticlesFor(int groupID) const throw (NewsGroupDoesNotExistException) override;
	std::vector<NewsGroup> listNewsGroups() const override;
	Article readArticle(int groupID, int articleID) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException) override;
	void writeArticle(int groupID, Article& article) throw (NewsGroupDoesNotExistException) override;
private:
	/* A map with group ID for keys and news groups for values. */
	std::map<int, NewsGroup> database;
};
#endif