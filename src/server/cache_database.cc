#include "Database.h"
#include <string>
#include <vector>

using namespace std;

class CacheDatabase : public Database {
public:

	CacheDatabase(){

	
	}

	virtual vector<pair<int, string& ngName>>& listNewsGroups() const{
		vector<pair<int, string& ngName>> v;
		return v;
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


};
