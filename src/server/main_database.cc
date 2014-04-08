#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "main_database.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

MainDatabase::MainDatabase(){
	initDatabase();
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
		closedir (databaseDir);
		delete group; 
	}
	//delete databaseDir;
	sort(groups.begin(), groups.end(), [](const NewsGroup & g1, const NewsGroup & g2){ return g1.id < g2.id;});
	return groups;
}

void MainDatabase::createNewsGroup(const string& groupName){
	string groupDirString = findFreeGroupPath();
	mkdir(groupDirString.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions
	ofstream nameFile;
	nameFile.open (groupDirString + "/GROUP_NAME");
	nameFile << groupName;
	nameFile.close();
}

void MainDatabase::deleteNewsGroup(int groupID){
	string groupDirString = databaseRootPath + "/" + to_string(groupID);
	DIR *groupDir = opendir(groupDirString.c_str());

	if(groupDir != nullptr){
		struct dirent *dirEnt = nullptr;
		while (dirEnt = readdir (groupDir)){
			string entryName(dirEnt->d_name);
			if(entryName != ".." && entryName != "."){
				string entryPath(groupDirString + "/" + entryName);
				remove(entryPath.c_str());
			}
		}
		rmdir(groupDirString.c_str());
		//delete dirent ;
	}else{
		//throw exception;
	}
	closedir (groupDir);
}

vector<Article> MainDatabase::listArticlesFor(int groupID) const{
	vector<Article> articles;
	DIR *groupDir = openGroupDir(groupID);

	if(groupDir != nullptr){
		struct dirent *dirEnt;
		while (dirEnt = readdir (groupDir)){
			string entryName(dirEnt->d_name);
			if(entryName != "." && entryName != ".." && entryName != "GROUP_NAME"){
				string articlePath = databaseRootPath + to_string(groupID) + "/" + entryName;
				articles.push_back(makeArticle(groupID, stoi(entryName)));
			}
		}
		closedir(groupDir);
		//delete groupDir;
		//delete (dirent);
	}else{
		cout << "fskoa";
		//group not found, throw exception
	}
	sort(articles.begin(), articles.end(), [](const Article & a1, const Article & a2){ return a1.id < a2.id;});
	return articles;
}

Article MainDatabase::readArticle(int groupID, int articleID) const{
	return makeArticle(groupID, articleID);
}

void MainDatabase::writeArticle(int groupID, Article& article) {
	string articlePath = findFreeArticlePath(groupID);
	saveArticleToFile(article, articlePath);
}

void MainDatabase::deleteArticle(int groupID, int articleID){
	string articlePath = databaseRootPath + to_string(groupID) + "/" + to_string(articleID);
	remove(articlePath.c_str());
}

Article MainDatabase::makeArticle(int groupID, int articleID) const{
	ifstream articleStream(databaseRootPath + to_string(groupID) + "/" + to_string(articleID));
	string title, author, text, line;
	articleStream >> title;
	articleStream >> author;

	while(!articleStream.eof()){
		getline(articleStream, line);
		text = text + line + "\n";
	}
	articleStream.close();
	return Article(title, author, text);
}

NewsGroup MainDatabase::makeGroup(int groupID) const{
	ifstream articleStream(databaseRootPath + to_string(groupID) + "/" + "GROUP_NAME");
	string groupName;
	articleStream >> groupName;
	articleStream.close();
	return NewsGroup(groupName, groupID);
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

DIR* MainDatabase::openGroupDir(int groupID)  const{
	string groupDirString(databaseRootPath + to_string(groupID));
	return opendir(groupDirString.c_str());
}

/* Returns an unused article path in the directory of the given group. */
string MainDatabase::findFreeArticlePath(int groupID)  const{
	int freeArticleID = -1;
	string groupPath = databaseRootPath + to_string(groupID) + "/";
	string articlePath;
	DIR* existingArticle = nullptr;

	do{
		/* All encountered existing articles are closed here. */
		if(existingArticle != nullptr){
			closedir(existingArticle);
		}
		++freeArticleID;
		articlePath = groupPath + to_string(freeArticleID);

		/* If the existingArticle is not a nullptr, 
		the articlePath is used by an existing article.
		We close it and increment the articleID */
	}while((existingArticle = opendir(articlePath.c_str())) != nullptr);
	return articlePath;
}

void MainDatabase::saveArticleToFile(Article& article, string& articlePath) const{
	ofstream nameFile(articlePath);
	nameFile << article.title << endl;
	nameFile << article.author << endl;
	nameFile << article.text << endl;
	nameFile.close();
}

void MainDatabase::initDatabase() const{
	if (opendir(databaseRootPath.c_str()) == nullptr){
		cout << "Creating root directory..." << endl;
		mkdir(databaseRootPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions
	}
}
