#ifndef MAIN_DATABASE_H
#define MAIN_DATABASE_H
#include "database.h"
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>

/* A news group database that stores all data on the hard drive.
	This class derives from the abstract base class Database. 
	See file database.h for documentation of the overridden methods. */
class MainDatabase : public Database {
public:
	MainDatabase();
	void createNewsGroup(const std::string& groupName) throw (NewsGroupAlreadyExistsException) override;
	void deleteArticle(int groupID, int articleID) throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException) override;
	void deleteNewsGroup(int groupID) throw (NewsGroupDoesNotExistException) override;
	std::vector<Article> listArticlesFor(int groupID) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException) override;
	std::vector<NewsGroup> listNewsGroups() const override;
	Article readArticle(int groupID, int articleID)  const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException) override;
	void writeArticle(int groupID, Article&) throw (NewsGroupDoesNotExistException) override;
private:
	/* Path to the database root folder. */ 
	const std::string databaseRootPath = "./database/";

	/* Name of the group name files */ 
	const std::string GROUP_NAME_FILE = ".GROUP_NAME";

	/* Name of the files containing the ID of the newest article ID. */
	const std::string LAST_ARTICLE_ID = ".LAST_ARTICLE_ID";

	/* Name of the file containing the ID of the newest group. */
	const std::string LAST_GROUP_ID = ".LAST_GROUP_ID";

	/* The path to the LAST_GROUP_ID file. */
	const std::string GROUP_ID_PATH = databaseRootPath + LAST_GROUP_ID;

	/* Returns the name of the group with ID groupID. */
	std::string getGroupName(int groupID) const;

	/* Returns true if there exists a group with ID groupID. */
	bool groupExists(int groupID) const;

	/* Returns true if there exists a group named groupName. */
	bool groupExists(const std::string& groupName) const;

	/* Initializes the database. */
	void initDatabase();

	/* Loads the last group ID into the program. */
	void loadLastGroupID();

	/* Loads the last article ID into the program. */
	int loadLastArticleID(int groupID) const;

	/* Creates an empty Article object with the given IDs. 
		Used for listing of articles. */
	Article makeArticle(int groupID, int articleID) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException);

	/* Creates an empty NewsGroup object with the given ID.
		Used for listing of news groups. */
	NewsGroup makeGroup(int groupID) const;

	/* Returns a DIR pointer to the directory of the group with ID groupID. */
	DIR* openGroupDir(int groupID) const;

	/* Saves the given article to the given path. */
	void saveArticleToFile(Article& article, std::string& articlePath) const;

	/* Saves articleID as the last article ID of the group with groupID to file. */
	void saveLastArticleID(int groupID, int articleID);

	/* Saves latestNewsGroupID to file. */
	void saveLastGroupID();
};
#endif