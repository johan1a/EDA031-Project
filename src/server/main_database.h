#ifndef MAIN_DATABASE_H
#define MAIN_DATABASE_H
#include "database.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

class MainDatabase : public Database {
public:
	MainDatabase();
	void createNewsGroup(const std::string& groupName) override;
	void deleteArticle(int groupID, int articleID) override;
	void deleteNewsGroup(int groupID) override;
	std::vector<Article> listArticlesFor(int groupID) const override;
	std::vector<NewsGroup> listNewsGroups() const override;
	Article readArticle(int groupID, int articleID) const override;
	void writeArticle(int groupID, Article&) override;
private:
	std::string databaseRootPath = "./database/";
	std::string findFreeArticlePath(int groupID) const;
	std::string findFreeGroupPath() const;
	std::string getGroupName(int groupID) const;
	bool groupExists(int groupID) const;
	bool groupExists(const std::string& groupName) const;
	void initDatabase() const;
	Article makeArticle(int groupID, int articleID) const;
	NewsGroup makeGroup(int groupID) const;
	DIR* openGroupDir(int groupID) const;
	void saveArticleToFile(Article& article, std::string& articlePath) const;
};
#endif