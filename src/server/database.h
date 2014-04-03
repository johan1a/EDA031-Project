#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>


struct Article{
	int id;
	std::string title;
	std::string author;
	std::string text;
};

struct NewsGroup{
	std::string name;
	std::vector<Article> articles;
	int latestArticleId;
	NewsGroup(std::string n) : name(n), articles(), latestArticleId() {}
};

class Database{
public:
	virtual std::vector<std::pair<int, std::string> > listNewsGroups() const;
	virtual void createNewsGroup(const std::string&); //throws NewsGroupAlreadyExistsException
	virtual void deleteNewsGroup(int); //throws NewsGroupDoesNotExistException
	virtual std::vector<std::pair<int, std::string> > listArticlesFor(int) const; //throws NewsGroupDoesNotExistException
	virtual Article readArticle(int, int) const; //throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	virtual void writeArticle(int, Article&); //NewsGroupDoesNotExistException
	virtual void deleteArticle(int, int); //throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	int latestNewsGroupId;
};

#endif
