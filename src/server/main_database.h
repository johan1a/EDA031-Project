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
	int freeArticleID;
	int freeGroupID;
	const std::string databaseRootPath = "./database/";
	const std::string IDFILE = "./database/FREE_IDS";
	const std::string GROUP_NAME_FILE = "/GROUP_NAME";
	void loadFreeIDS();
	void saveFreeIDS();
	std::string getGroupName(int groupID) const;
	bool groupExists(int groupID) const;
	bool groupExists(const std::string& groupName) const;
	void initDatabase();
	Article makeArticle(int groupID, int articleID) const;
	NewsGroup makeGroup(int groupID) const;
	DIR* openGroupDir(int groupID) const;
	void saveArticleToFile(Article& article, std::string& articlePath) const;
};
#endif