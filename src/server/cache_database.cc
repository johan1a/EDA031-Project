#include "cache_database.h"
#include <map>
#include "../common/exception/news_group_already_exists_exception.h"
#include "../common/exception/news_group_does_not_exist_exception.h"
#include "../common/exception/article_does_not_exist_exception.h"
#include <iostream>
#include <algorithm>

using namespace std;

CacheDatabase::CacheDatabase(){
	latestNewsGroupID = 0;	
	cout << "Database initialized." << endl;
}

void CacheDatabase::createNewsGroup(const string& ngName) throw (NewsGroupAlreadyExistsException){
	NewsGroup ng(ngName);
	ng.id = ++latestNewsGroupID;
	auto iter = find_if(database.begin(), database.end(), 
												[ngName](pair<int, NewsGroup> p){ return p.second.name == ngName; });
	if(iter != database.end()){
		throw NewsGroupAlreadyExistsException();
	}
	database.insert(make_pair(latestNewsGroupID, ng));
}

void CacheDatabase::deleteArticle(int ngId, int artId) throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException){
	auto it = database.find(ngId);
	if(it == database.end()){
		throw NewsGroupDoesNotExistException();
	} else {
		auto iter = find_if(it->second.articles.begin(), it->second.articles.end(), 
													[artId](Article a){ return artId  == a.id; });
		if(iter == it->second.articles.end()){
			throw ArticleDoesNotExistException();
		} else {
			it->second.articles.erase(iter);
		}
	}
}

void CacheDatabase::deleteNewsGroup(int id) throw (NewsGroupDoesNotExistException){
	size_t i = database.erase(id);
	if(!i){
		throw NewsGroupDoesNotExistException();
	}
}

vector<Article> CacheDatabase::listArticlesFor(int id) const throw (NewsGroupDoesNotExistException){
	auto it = database.find(id);
	if(it == database.end()){
		throw NewsGroupDoesNotExistException();
	} else {
		return it->second.articles;
	}
}

vector<NewsGroup> CacheDatabase::listNewsGroups() const{
	vector<NewsGroup> v;
	for(auto it = database.begin(); it != database.end(); ++it){
		v.push_back(it->second);
	}
	return v;
}

Article CacheDatabase::readArticle(int ngId, int artId) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException){
	auto it = database.find(ngId);
	if(it == database.end()){
		throw NewsGroupDoesNotExistException();
	} else {
		auto iter = find_if(it->second.articles.begin(), it->second.articles.end(), 
													[artId](Article a){ return artId == a.id; });
		if(iter == it->second.articles.end()){
			throw ArticleDoesNotExistException();
		} else {
			return *iter;
		}
	}
}

void CacheDatabase::writeArticle(int id, Article& art) throw (NewsGroupDoesNotExistException){
	auto it = database.find(id);
	if(it == database.end()){
		throw NewsGroupDoesNotExistException();
	} else {
		art.id = ++(it->second.latestArticleId);
		it->second.articles.push_back(art);
	}
}
