#include "database.h"
#include <string>
#include <vector>
#include <map>
#include "news_group_already_exists_exception.h"
#include "news_group_does_not_exist_exception.h"
#include "article_does_not_exist_exception.h"
#include <iostream>
#include <algorithm>


using namespace std;
typedef map<string, vector<Article> >::const_iterator iter_type;
 

class CacheDatabase : public Database {

public:

	CacheDatabase(){
		latestNewsGroupId = 0;	
	}

	virtual vector<NewsGroup> listNewsGroups() const{
		vector<NewsGroup> v(database.size());
		for(auto it = database.begin(); it != database.end(); ++it){
			v.push_back(it->second);
		}
		return v;
	}
	
	virtual void createNewsGroup(const string& ngName){
		NewsGroup ng(ngName);
		ng.id = ++latestNewsGroupId;
		auto it = database.insert(make_pair(latestNewsGroupId, ng));
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

	virtual vector<Article> listArticlesFor(int id) const{
		auto it = database.find(id);
		if(it == database.end()){
			throw NewsGroupDoesNotExistException();
		} else {
			return it->second.articles;
		}
	}

	virtual Article readArticle(int ngId, int artId) const{
		auto it = database.find(ngId);
		if(it == database.end()){
			throw NewsGroupDoesNotExistException();
		} else {
			auto iter = find_if(it->second.articles.begin(), it->second.articles.end(), 
														[artId](Article a){ return artId  == a.id; });
			if(iter == it->second.articles.end()){
				throw ArticleDoesNotExistException();
			} else {
				return *iter;
			}
		}
	}

	virtual void writeArticle(int id, Article& art){
		auto it = database.find(id);
		if(it == database.end()){
			throw NewsGroupDoesNotExistException();
		} else {
			art.id = ++(it->second.latestArticleId);
			it->second.articles.push_back(art);
		}
	}

	virtual void deleteArticle(int ngId, int artId){
		auto it = database.find(ngId);
		if(it == database.end()){
			throw NewsGroupDoesNotExistException();
		} else {
			auto iter = find_if(it->second.articles.begin(), it->second.articles.end(), 
														[artId](Article a){ return artId  == a.id; });
			if(iter == it->second.articles.end()){
				throw ArticleDoesNotExistException();
			} else {
				it->second.articles.erase(iter, iter);
			}
		}
	}

private:
	map<int, NewsGroup> database;
};




