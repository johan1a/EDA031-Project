#include "Database.h"
#include <string>

using namespace std;

class MainDatabase : public Database {
public:

	MainDatabase(){}

	virtual string& listNewsGroups() const{
		map<string& newsGroup, map<string& atricleName, string& theText>>::iterator it;
		string s("");
		for(it = database.begin(); it != database.end(); ++it){
			s.append(it->first);
			s.append(endl);
		}
		if(s == ""){
			s.apppend("No news groups in database.");
			s.apppend(endl);
			return s;
		}
		return s;
	}

	virtual string& createNewsGroup(const string& ngName){
		string s("");
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

