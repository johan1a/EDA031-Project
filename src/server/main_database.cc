#include "database.h"
#include <string>
#include <vector>

using namespace std;

class MainDatabase : public Database {
public:

	MainDatabase(){}

	virtual vector<pair<int, string& ngName>>& listNewsGroups() const{
		map<string& newsGroup, map<string& atricleName, string& theText>>::iterator it;
		vector<pair<int, string& ngName>> newsGroups;
		int i = 1;
		for(it = database.begin(); it != database.end(); ++it){
			pair<int, string& ngName> p = make_pair(i, it->first);;
			newsGroups.push_back();
			++i;
		}
		if(newsGroups.empty()){
			string s("No newsgroups in database.");
			pair<int, string& ngName> p = make_pair(i, s);
			newsGroups.push_back(p);
		}
		return newsGroups;
	}

	virtual string& createNewsGroup(const string& ngName){
		string s("");
		if(database.){
			
		}

		return s;
	}

	virtual string& deleteNewsGroup(const string& ngName){
		string s("");
		return s;
	}

	virtual string& listArticlesFor(const string& ngName){
		string s("");
		return s;
	}

	virtual string& readArticle(const string& articleName, const string& ngName){
		string s("");
		return s;
	}

	virtual string& writeArticle(const string& articleName, const string& ngName){
		string s("");
		return s;
	}

	virtual string& deleteArticle(const string& articleName, const string& ngName){
		string s("");
		return s;
	}

private:
	map<string& newsGroup, map<string& atricleName, string& theText>> database;
};

