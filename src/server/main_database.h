#ifndef MAIN_DATABASE_H
#define MAIN_DATABASE_H
#include <string>
#include <vector>
#include <iostream>
#include "database.h"

/*
struct Article{
	std::string title;
	std::string author;
	std::string text;
	int id;
	Article(std::string ti, std::string au, std::string te) : title(ti), author(au), text(te), id() {}
};

struct NewsGroup{
	std::string name;
	std::vector<Article> articles;
	int latestArticleId;
	int id;
	NewsGroup(std::string n) : name(n), articles(), latestArticleId(), id() {}
	NewsGroup() : name(), articles(), latestArticleId(), id() {}
};
*/

class MainDatabase : public Database {
public:
	MainDatabase();
	virtual std::vector<NewsGroup> listNewsGroups() const;
	virtual void createNewsGroup(const std::string&); //throws NewsGroupAlreadyExistsException
	virtual void deleteNewsGroup(int); //throws NewsGroupDoesNotExistException
	virtual std::vector<Article> listArticlesFor(int) const; //throws NewsGroupDoesNotExistException
	virtual Article readArticle(int, int) const; //throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	virtual void writeArticle(int, Article&); //NewsGroupDoesNotExistException
	virtual void deleteArticle(int, int); //throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
protected:
	int latestNewsGroupId;
};

#endif
