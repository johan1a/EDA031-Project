#ifndef DATABASE_H
#define DATABASE_H
#include <string>
#include <vector>

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

class Database{
public:
	virtual std::vector<NewsGroup> listNewsGroups() const;
	virtual void createNewsGroup(const std::string&);
	virtual void deleteNewsGroup(int);
	virtual std::vector<Article> listArticlesFor(int) const;
	virtual Article readArticle(int, int) const;
	virtual void writeArticle(int, Article&);
	virtual void deleteArticle(int, int);
protected:
	int latestNewsGroupId;
};

#endif
