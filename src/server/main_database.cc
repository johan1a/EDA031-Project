#include "main_database.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

MainDatabase::MainDatabase(){
	latestNewsGroupID = 0;
	initDatabase();
	cout << "Database initialized." << endl;
}

void MainDatabase::createNewsGroup(const string& groupName) throw (NewsGroupAlreadyExistsException){
	if(!groupExists(groupName)){
		string groupPath = databaseRootPath + to_string(++latestNewsGroupID);
		mkdir(groupPath.c_str(), S_IRWXU | S_IROTH);
		ofstream nameFile(groupPath + "/" + GROUP_NAME_FILE);
		nameFile << groupName;
		nameFile.close();
		saveLastGroupID();
	}else{
		throw NewsGroupAlreadyExistsException();
	}
}

void MainDatabase::deleteArticle(int groupID, int articleID) throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException){
	if(groupExists(groupID)){
		string articlePath = databaseRootPath + to_string(groupID) + "/" + to_string(articleID);
		if(remove(articlePath.c_str()) != 0){
			throw ArticleDoesNotExistException();
		}
	}else{
		throw NewsGroupDoesNotExistException();
	}
}

void MainDatabase::deleteNewsGroup(int groupID) throw (NewsGroupDoesNotExistException){
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

vector<Article> MainDatabase::listArticlesFor(int groupID) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException){
	vector<Article> articles;
	DIR *groupDir = openGroupDir(groupID);
	if(groupDir != nullptr){
		struct dirent *dirEnt;
		while ((dirEnt = readdir (groupDir))){
			string entryName(dirEnt->d_name);
			if(entryName != "." && entryName != ".." && entryName != GROUP_NAME_FILE && entryName != LAST_ARTICLE_ID){
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
			if(groupID != "." && groupID != ".." && groupID != LAST_GROUP_ID){
				groups.push_back(makeGroup(stoi(groupID)));
			}
		}
		delete group;
		closedir (databaseDir);
	}
	sort(groups.begin(), groups.end(), [](const NewsGroup & g1, const NewsGroup & g2){ return g1.id < g2.id; });
	return groups;
}

Article MainDatabase::readArticle(int groupID, int articleID) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException){
	return makeArticle(groupID, articleID);
}

void MainDatabase::writeArticle(int groupID, Article& article) throw (NewsGroupDoesNotExistException){
		if(!groupExists(groupID)){
			throw NewsGroupDoesNotExistException();
		}
		string groupPath = databaseRootPath + to_string(groupID) + "/";
		int artID = loadLastArticleID(groupID) + 1;
		string articlePath = groupPath + to_string(artID);
		saveArticleToFile(article, articlePath);
		saveLastArticleID(groupID, artID);
		saveLastGroupID();
}

string MainDatabase::getGroupName(int groupID) const{
	ifstream groupStream(databaseRootPath + to_string(groupID) + "/" + GROUP_NAME_FILE);
	string groupName;
	getline(groupStream, groupName);
	groupStream.close();
	return groupName;
}

bool MainDatabase::groupExists(int groupID) const{
	string groupPath(databaseRootPath + to_string(groupID));
	return openGroupDir(groupID);
}

bool MainDatabase::groupExists(const string& groupName) const{
	DIR* root = opendir(databaseRootPath.c_str());
	struct dirent* group;
	while((group = readdir(root))){
		string groupID(group->d_name);
		if(groupID != ".." && groupID != "." && groupID != LAST_GROUP_ID){
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

void MainDatabase::initDatabase(){
	if (!opendir(databaseRootPath.c_str())){
		cout << "Creating root directory..." << endl;
		mkdir(databaseRootPath.c_str(), S_IRWXU | S_IROTH );
		latestNewsGroupID = 0;
		saveLastGroupID();
	}else{
		loadLastGroupID();
	}
}

void MainDatabase::loadLastGroupID(){
	ifstream idStream(GROUP_ID_PATH);
	if(idStream){
		string id;
		idStream >> id;
		latestNewsGroupID = stoi(id);
		idStream.close();
	}
}

int MainDatabase::loadLastArticleID(int groupID) const{
	string idPath = databaseRootPath + to_string(groupID) + "/" + LAST_ARTICLE_ID;
	ifstream idStream(idPath);
	
	string id = "0";
	if(idStream){
		idStream >> id;
		idStream.close();
	}else{
		ofstream outStream(idPath);
		outStream << id;
		outStream.close();
	}
	return stoi(id);
}

Article MainDatabase::makeArticle(int groupID, int articleID) const throw (ArticleDoesNotExistException, NewsGroupDoesNotExistException) {
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
	ifstream groupStream(databaseRootPath + to_string(groupID) + "/" + GROUP_NAME_FILE);
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

void MainDatabase::saveLastArticleID(int groupID, int articleID){
	string idPath = databaseRootPath + to_string(groupID) + "/" + LAST_ARTICLE_ID;
	ofstream idStream(idPath);
	idStream << articleID;
	idStream.close();
}

void MainDatabase::saveLastGroupID(){
		ofstream idFile(GROUP_ID_PATH);
		idFile << latestNewsGroupID << endl;
		idFile.close();	
}
