#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>


struct Article{
	std::string title;
	std::string author;
	std::string text;
};

class Database{
public:

	virtual std::vector<std::pair<int, std::string> > listNewsGroups() const;
	virtual void createNewsGroup(const std::string&); //throws NewsGroupAlreadyExistsException
	virtual void deleteNewsGroup(int); //throws NewsGroupDoesNotExistException
	virtual std::vector<std::pair<int, std::string> > listArticlesFor(int) const; //throws NewsGroupDoesNotExistException
	virtual article readArticle(int, int) const; //throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	virtual void writeArticle(int, article&); //NewsGroupDoesNotExistException
	virtual void deleteArticle(int, int); //throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	



};

#endif
