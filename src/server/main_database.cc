#include "database.h"
#include <string>
#include <vector>
#include <map>


using namespace std;
typedef map<string, map<string, string> >::const_iterator iter_type;

class MainDatabase : public Database {

public:

	MainDatabase(){}

	virtual vector<pair<int, string> >& listNewsGroups() const{
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

	virtual string& createNewsGroup(const string& ngName){
		string s("");
		//if(database.){
		//	
		//}

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
	map<string, map<string, string> > database;
};



