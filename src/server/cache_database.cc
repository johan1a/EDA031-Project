#include "database.h"
#include <string>
#include <vector>
#include <map>
#include "news_group_already_exists_exception.h"
#include "news_group_does_not_exist_exception.h"
#include <iostream>


using namespace std;
typedef map<string, vector<Article> >::const_iterator iter_type;
 

class CacheDatabase : public Database {

public:

	CacheDatabase(){
		latestNewsGroupId = 0;	
	}

	virtual vector<pair<int, string> > listNewsGroups() const{
		vector<pair<int, string> > newsGroups;
/*		int i = 1;
		pair<int, string> p;
		for(iter_type it = database.begin(); it != database.end(); ++it){
			p = make_pair(i, it->first);
			newsGroups.push_back(p);
			++i;
		}
		if(newsGroups.empty()){
			string s("No newsgroups in database.");
			pair<int, string> p = make_pair(i, s);
			newsGroups.push_back(p);
		}*/
		return newsGroups;
	}
	
	virtual void createNewsGroup(const string& ngName){
		NewsGroup ng = NewsGroup(ngName);
		auto it = database.insert(make_pair(++latestNewsGroupId, ng));
		if(!it.second){
			throw NewsGroupAlreadyExistsException();
		}
	}
	
	virtual void deleteNewsGroup(int id){
		size_t i = database.erase(id);
		if(!i){
			throw NewsGroupDoesNotExistException();
		}
	}

	virtual vector<Article> listArticlesFor(int id){
		auto it = database.find(id);
		if(it == database.end()){
			throw NewsGroupDoesNotExistException();
		} else {
			return it->second.articles;
		}
	}

	//throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	virtual Article readArticle(int, int) const{
		
	}

	//NewsGroupDoesNotExistException
	virtual void writeArticle(int, Article&){
		
	}

	//throws NewsGroupDoesNotExistException, ArticleDoesNotExistException
	virtual void deleteArticle(int, int){
		
	}

private:
	map<int, NewsGroup> database;	//newsgroup, articles
};




