#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>

struct Article{
	std::string title;
	std::string author;
	std::string text;
	int id;
	Article() {}
	Article(std::string& ti, std::string& au, std::string& te, int ID) : title(ti), author(au), text(te), id(ID) {}
	Article(std::string& ti, std::string& au, std::string& te) : title(ti), author(au), text(te), id() {}
	Article(std::string& ti, std::string& au) : title(ti), author(au) {} //används denna?
};

struct NewsGroup{
	std::string name;
	std::vector<Article> articles;
	int latestArticleId;
	int id;
	NewsGroup(std::string n, int ID) : name(n), articles(), latestArticleId(), id(ID) {}
	NewsGroup(std::string n) : name(n), articles(), latestArticleId(), id() {}
	NewsGroup() : name(), articles(), latestArticleId(), id() {}

};

/* Abstract database base class. 
Describes methods for creating, 
deleting and listing newsgroups and articles.*/
class Database{
public:
	virtual ~Database() = default;

	/* Creates a news group with the name groupName and stores it
	int the database. */
	virtual void createNewsGroup(const std::string& groupName) = 0;

	/* Deletes the article with the given article ID in the group
	with the given group ID. */
	virtual void deleteArticle(int groupID, int articleID) = 0;

	/* Deletes the news group with the given group id. */
	virtual void deleteNewsGroup(int groupID) = 0;

	/* Lists all the articles of the group with the given group ID. */
	virtual std::vector<Article> listArticlesFor(int groupID) const = 0;

	/* Lists all news groups. */
	virtual std::vector<NewsGroup> listNewsGroups() const = 0;

	/* Returns the article the given article ID in the group
	with the given group ID. */
	virtual Article readArticle(int groupID, int articleID) const = 0;
	
	/* Stores the given article of the group with the given group ID in the database. */
	virtual void writeArticle(int groupID, Article&) = 0;
protected:
	/* The ID of the newest news group. */
	int latestNewsGroupID;
};

#endif
