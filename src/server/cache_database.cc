#include "database.h"
#include <string>
#include <vector>
#include <map>
#include "news_group_already_exists_exception.h"
#include <iostream>


using namespace std;
typedef map<string, vector<Article> >::const_iterator iter_type;
 

class CacheDatabase : public Database {

public:

	CacheDatabase(){}

	virtual vector<pair<int, string> > listNewsGroups() const{
		vector<pair<int, string> > newsGroups;
		int i = 1;
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
		}
		return newsGroups;
	}
	
	virtual void createNewsGroup(const string& ngName){
		vector<Article> v; 	
		auto it = database.insert(make_pair(ngName, v));
		if(!it.second){
			throw NewsGroupAlreadyExistsException();
		}
	}
	
	//throws NewsGroupDoesNotExistException
	virtual void deleteNewsGroup(int){

	}
	
	//throws NewsGroupDoesNotExistException
	virtual vector<std::pair<int, std::string> > listArticlesFor(int){
		vector<std::pair<int, std::string> > v;
		return v;
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

	map<string, vector<Article> > database;	//newsgroup, articles

	bool containsNewsGroup(const string& ngName){
		iter_type it = database.find(ngName);
		return (it != database.end());	
	};

	bool containsArticle(const string& articleName, const string& ngName){
		if(containsNewsGroup(ngName)){
//			auto it = database.find(ngName);
	//		auto articlePos = find_if();
		//	return (articlePos != it->second.end());
		}
		return false;
	};

};




