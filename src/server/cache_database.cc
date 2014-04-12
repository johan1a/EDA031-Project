#include "cache_database.h"
#include <map>
#include "../common/exception/news_group_already_exists_exception.h"
#include "../common/exception/news_group_does_not_exist_exception.h"
#include "../common/exception/article_does_not_exist_exception.h"
#include <iostream>
#include <algorithm>

using namespace std;

CacheDatabase::CacheDatabase(){
	latestNewsGroupId = 0;	
}

vector<NewsGroup> CacheDatabase::listNewsGroups() const{
	vector<NewsGroup> v;
	for(auto it = database.begin(); it != database.end(); ++it){
		v.push_back(it->second);
	}
	return v;
}

void CacheDatabase::createNewsGroup(const string& ngName){
	NewsGroup ng(ngName);
	ng.id = ++latestNewsGroupId;
	auto iter = find_if(database.begin(), database.end(), 
												[ngName](pair<int, NewsGroup> p){ return p.second.name == ngName; });
	if(iter != database.end()){
		throw NewsGroupAlreadyExistsException();
	}
	database.insert(make_pair(latestNewsGroupId, ng));
}

void CacheDatabase::deleteNewsGroup(int id){
	size_t i = database.erase(id);
	if(!i){
		throw NewsGroupDoesNotExistException();
	}
}

vector<Article> CacheDatabase::listArticlesFor(int id) const{
	auto it = database.find(id);
	if(it == database.end()){
		throw NewsGroupDoesNotExistException();
	} else {
		return it->second.articles;
	}
}

Article CacheDatabase::readArticle(int ngId, int artId) const{
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

void CacheDatabase::writeArticle(int id, Article& art){
	auto it = database.find(id);
	if(it == database.end()){
		throw NewsGroupDoesNotExistException();
	} else {
		art.id = ++(it->second.latestArticleId);
		it->second.articles.push_back(art);
	}
}

void CacheDatabase::deleteArticle(int ngId, int artId){
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




