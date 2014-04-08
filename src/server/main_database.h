#ifndef MAIN_DATABASE_H
#define MAIN_DATABASE_H
#include "database.h"
#include <string>
#include <vector>

class MainDatabase : Database {
public:
	MainDatabase();
	virtual std::vector<NewsGroup> listNewsGroups() const override;
	virtual void createNewsGroup(const std::string&) override;
	virtual void deleteNewsGroup(int) override;
	virtual std::vector<Article> listArticlesFor(int) const override;
	virtual Article readArticle(int, int) const override;
	virtual void writeArticle(int, Article&) override;
	virtual void deleteArticle(int, int) override;
private:
	std::string databaseRootPath = "./database/";
	std::string groupDir = "./groups";
	void initDatabase();
};
#endif