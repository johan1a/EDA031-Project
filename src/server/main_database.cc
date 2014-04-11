#include "news_group_already_exists_exception.h"
#include "news_group_does_not_exist_exception.h"
#include "article_does_not_exist_exception.h"
#include "main_database.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

MainDatabase::MainDatabase(){
	initDatabase();
	cout << "Database initialized..." << endl;
}

void MainDatabase::createNewsGroup(const string& groupName){
	if(!groupExists(groupName)){
		string groupPath = findFreeGroupPath();
		mkdir(groupPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions
		ofstream nameFile(groupPath + GROUP_NAME_FILE);
		nameFile << groupName;
		nameFile.close();
	}else{
		throw NewsGroupAlreadyExistsException();
	}
}

void MainDatabase::deleteArticle(int groupID, int articleID){
	if(groupExists(groupID)){
		string articlePath = databaseRootPath + to_string(groupID) + "/" + to_string(articleID);
		if(remove(articlePath.c_str()) != 0){
			throw ArticleDoesNotExistException();
		}
	}else{
		throw NewsGroupDoesNotExistException();
	}
}

void MainDatabase::deleteNewsGroup(int groupID){
	string groupPath = databaseRootPath + to_string(groupID);
	DIR *groupDir = opendir(groupPath.c_str());
	if(groupDir != nullptr){
		struct dirent *dirEnt = nullptr;
		while ((dirEnt = readdir (groupDir))){
			string entryName(dirEnt->d_name);
			if(entryName != ".." && entryName != "."){
				string entryPath(groupPath + "/" + entryName);
				remove(entryPath.c_str());
			}
		}
		delete dirEnt;
		rmdir(groupPath.c_str());
		closedir(groupDir);
	}else{
		throw NewsGroupDoesNotExistException();
	}
}

vector<Article> MainDatabase::listArticlesFor(int groupID) const{
	vector<Article> articles;
	DIR *groupDir = openGroupDir(groupID);
	if(groupDir != nullptr){
		struct dirent *dirEnt;
		while ((dirEnt = readdir (groupDir))){
			string entryName(dirEnt->d_name);
			if(entryName != "." && entryName != ".." && entryName != "GROUP_NAME"){
				articles.push_back(makeArticle(groupID, stoi(entryName)));
			}
		}
		delete dirEnt;
		closedir(groupDir);
	}else{
		throw NewsGroupDoesNotExistException();
	}
	sort(articles.begin(), articles.end(), [](const Article& a1, const Article& a2){ return a1.id < a2.id; });
	return articles;
}

vector<NewsGroup> MainDatabase::listNewsGroups() const{
	vector<NewsGroup> groups;
	DIR *databaseDir = opendir(databaseRootPath.c_str());
	if(databaseDir != nullptr){
		struct dirent *group = nullptr;
		while ((group = readdir (databaseDir)) != nullptr){
			string groupID(group->d_name);
			if(groupID != "." && groupID != ".."){
				groups.push_back(makeGroup(stoi(groupID)));
			}
		}
		delete group;
		closedir (databaseDir);
	}
	sort(groups.begin(), groups.end(), [](const NewsGroup & g1, const NewsGroup & g2){ return g1.id < g2.id; });
	return groups;
}

Article MainDatabase::readArticle(int groupID, int articleID) const{
	return makeArticle(groupID, articleID);
}

void MainDatabase::writeArticle(int groupID, Article& article) {
	try{
		string articlePath = findFreeArticlePath(groupID);
		saveArticleToFile(article, articlePath);
	}catch(NewsGroupDoesNotExistException e){
		throw NewsGroupDoesNotExistException();
	}
}

string MainDatabase::findFreeGroupPath() const{
	int freeGroupID = -1;
	string groupPath;
	DIR *groupDir = nullptr;
	do {
		if(groupDir != nullptr){
			closedir(groupDir);
		}
		++freeGroupID;
		groupPath = databaseRootPath + to_string(freeGroupID);
	} while((groupDir = opendir(groupPath.c_str())) != nullptr);
	return groupPath;
}

/* Returns an unused article path in the directory of the given group. */
string MainDatabase::findFreeArticlePath(int groupID)  const{
	string articlePath;
	if(groupExists(groupID)){
		int freeArticleID = -1;
		string groupPath = databaseRootPath + to_string(groupID) + "/";
		ifstream existingArticle;
		do{
			existingArticle.close();
			++freeArticleID;
			articlePath = groupPath + to_string(freeArticleID);
			existingArticle.open(articlePath);
		}while(existingArticle);
	}else{
		throw NewsGroupDoesNotExistException();
	}
	return articlePath;
}

string MainDatabase::getGroupName(int groupID) const{
	ifstream groupStream(databaseRootPath + to_string(groupID) + GROUP_NAME_FILE);
	string groupName;
	getline(groupStream, groupName);
	groupStream.close();
	return groupName;
}

bool MainDatabase::groupExists(int groupID) const{
	string groupPath(databaseRootPath + to_string(groupID));
	return opendir(groupPath.c_str()) != nullptr;
}

bool MainDatabase::groupExists(const string& groupName) const{
	DIR* root = opendir(databaseRootPath.c_str());
	struct dirent* group;
	while((group = readdir(root))){
		string groupID(group->d_name);
		if(groupID != ".." && groupID != "."){
			string otherGroupName = getGroupName(stoi(groupID));
			if(otherGroupName == groupName){
				closedir(root);
				return true;
			}
		}
	}
	delete group;
	closedir(root);
	return false;
}

void MainDatabase::initDatabase() const{
	if (opendir(databaseRootPath.c_str()) == nullptr){
		cout << "Creating root directory..." << endl;
		mkdir(databaseRootPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions
	}
}

Article MainDatabase::makeArticle(int groupID, int articleID) const{
	if(groupExists(groupID)){
		ifstream articleStream(databaseRootPath + to_string(groupID) + "/" + to_string(articleID));
		if(articleStream){
			string title, author, text, line;
			getline(articleStream, title);
			getline(articleStream, author);
			while(!articleStream.eof()){
				getline(articleStream, line);
				text += line;
				if(!articleStream.eof()){
					text += "\n";
				}
			}
			articleStream.close();
			return Article(title, author, text, articleID);
		}else{
			throw ArticleDoesNotExistException();
		}
	}else{
		throw NewsGroupDoesNotExistException();
	}
	return Article();
}

NewsGroup MainDatabase::makeGroup(int groupID) const{
	ifstream groupStream(databaseRootPath + to_string(groupID) + GROUP_NAME_FILE);
	string groupName;
	getline(groupStream, groupName);
	groupStream.close();
	return NewsGroup(groupName, groupID);
}

DIR* MainDatabase::openGroupDir(int groupID)  const{
	string groupPath(databaseRootPath + to_string(groupID));
	return opendir(groupPath.c_str());
}

void MainDatabase::saveArticleToFile(Article& article, string& articlePath) const{
	ofstream nameFile(articlePath);
	nameFile << article.title << endl;
	nameFile << article.author << endl;
	nameFile << article.text;
	nameFile.close();
}