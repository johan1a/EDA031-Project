#include <string>
#include <vector>
#include <iostream>
#include "database.h"
#include "main_database.h"


using namespace std;


MainDatabase::MainDatabase(){
	cout << "Cogito ergo sum" << endl;
}

std::vector<NewsGroup> MainDatabase::listNewsGroups() const{
	vector<NewsGroup> v;
	return v;
}

void MainDatabase::createNewsGroup(const string& ngName){
//	string s("");
//	return s;
}

void MainDatabase::deleteNewsGroup(int){
//	string s("");
//	return s;
}


std::vector<Article> MainDatabase::listArticlesFor(int) const {
	vector<Article> s;
	return s;
}


Article MainDatabase::readArticle(int, int) const {
	Article s("a","b","c");
	return s;
}

void MainDatabase::writeArticle(int, Article&) {
//	string s("");
//	return s;
}

void MainDatabase::deleteArticle(int, int){
//	string s("");
//	return s;
}


