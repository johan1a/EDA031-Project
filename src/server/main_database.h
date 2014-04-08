#ifndef MAIN_DATABASE_H
#define MAIN_DATABASE_H
#include "database.h"
#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
class MainDatabase : Database {
public:
	MainDatabase();
	std::vector<NewsGroup> listNewsGroups() const override;
	void createNewsGroup(const std::string& groupName) override;
	void deleteNewsGroup(int groupID) override;
	std::vector<Article> listArticlesFor(int groupID) const override;
	Article readArticle(int groupID, int articleID) const override;
	void writeArticle(int groupID, Article&) override;
	void deleteArticle(int groupID, int articleID) override;
private:
	std::string databaseRootPath = "./database/";
	std::string groupDir = "./groups";
	void initDatabase() const;
	Article makeArticle(int groupID, int articleID) const;
	NewsGroup makeGroup(int groupID) const;
	DIR* openGroupDir(int groupID) const;
	std::string findFreeArticlePath(int groupID) const;
	std::string findFreeGroupPath() const;
	void saveArticleToFile(Article& article, std::string& articlePath) const;
};
#endif