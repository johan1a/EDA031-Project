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
	Article(std::string& ti, std::string& au, std::string& te) : title(ti), author(au), text(te), id() {}
	Article(std::string& ti, std::string& au) : title(ti), author(au) {}
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

class Database{
public:
	virtual ~Database() = default;
	virtual std::vector<NewsGroup> listNewsGroups() const = 0;
	virtual void createNewsGroup(const std::string&) = 0;
	virtual void deleteNewsGroup(int groupID) = 0;
	virtual std::vector<Article> listArticlesFor(int groupID) const = 0;
	virtual Article readArticle(int groupID, int articleID) const = 0;
	virtual void writeArticle(int groupID, Article&) = 0;
	virtual void deleteArticle(int groupID, int articleID) = 0;
protected:
	int latestNewsGroupId;
};

#endif
