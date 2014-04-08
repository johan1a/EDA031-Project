#include <string>
#include <vector>
#include <dirent.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "main_database.h"
#include <iostream>
#include <fstream>

using namespace std;

MainDatabase::MainDatabase(){
	initDatabase();
	createNewsGroup("tjockisgruppen_lel");
	string title = "titel", author = "tjockis", text = "sdgkgdgdmgdmppmdasg";

	Article a(title,author,text);
	writeArticle(2,a);
	deleteArticle(2,0);
}

vector<NewsGroup> MainDatabase::listNewsGroups() const{
	vector<NewsGroup> v;

	DIR *databaseDir = nullptr;
	DIR *groupDir = nullptr;
	struct dirent *group = nullptr;
	struct dirent *dirEnt = nullptr;

	databaseDir = opendir(databaseRootPath.c_str());
	if(databaseDir != nullptr){
		while ((group = readdir (databaseDir)) != nullptr){
			string groupID(group->d_name);
			if(groupID != "." && groupID != ".."){
				string groupDirString (databaseRootPath + "/" + groupID);
				groupDir = opendir(groupDirString.c_str());
				
				if(groupDir != nullptr){
					while (dirEnt = readdir (groupDir)){
						string entryName(dirEnt->d_name);

						if(entryName == "GROUP_NAME"){
							ifstream articleStream;
							articleStream.open(databaseRootPath + "/" + groupID + "/" + entryName);
							string groupName;
							articleStream >> groupName;
							articleStream.close();
							v.push_back(NewsGroup(groupName, stoi(groupID)));
						}
					}
				}
			}
		}
		closedir (databaseDir);
	}
	return v;
}

void MainDatabase::createNewsGroup(const string& ngName){
	DIR *databaseDir = nullptr;
	DIR *groupDir = nullptr;

	databaseDir = opendir(databaseRootPath.c_str());

	int freeGroupID = 0;
	string groupDirString = databaseRootPath + "/" + to_string(freeGroupID);
	while((groupDir = opendir(groupDirString.c_str())) != nullptr){
		++freeGroupID;
		groupDirString = databaseRootPath + "/" + to_string(freeGroupID);
	}

	mkdir(groupDirString.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions

	ofstream nameFile;
	nameFile.open (groupDirString + "/GROUP_NAME");
	nameFile << ngName;
	nameFile.close();
	closedir (databaseDir);
	closedir (groupDir);
}

void MainDatabase::deleteNewsGroup(int ngID){
	DIR *groupDir = nullptr;
	struct dirent *dirEnt = nullptr;

	string groupDirString = databaseRootPath + "/" + to_string(ngID);
	groupDir = opendir(groupDirString.c_str());

	if(groupDir != nullptr){
		while (dirEnt = readdir (groupDir)){
			string entryName(dirEnt->d_name);
			string entryPath(groupDirString + "/" + entryName);
			remove(entryPath.c_str());
		}
		rmdir(groupDirString.c_str());
	}
	closedir (groupDir);
}

vector<Article> MainDatabase::listArticlesFor(int ngID) const{
	vector<Article> v;
	DIR *databaseDir = nullptr;
	DIR *groupDir = nullptr;
	struct dirent *group = nullptr;
	struct dirent *dirEnt = nullptr;

	databaseDir = opendir(databaseRootPath.c_str());
	if(databaseDir != nullptr){
		while ((group = readdir (databaseDir)) != nullptr){
			string groupID(group->d_name);
			if(groupID != ".." && groupID != "." && stoi(groupID) == ngID){
				string groupDirString (databaseRootPath + "/" + groupID);
				groupDir = opendir(groupDirString.c_str());
				
				if(groupDir != nullptr){
					while (dirEnt = readdir (groupDir)){
						string entryName(dirEnt->d_name);

						if(entryName != "." && entryName != ".." && entryName != "GROUP_NAME"){
							ifstream articleStream;
							articleStream.open(databaseRootPath + "/" + groupID + "/" + entryName);
							string title, author;
							articleStream >> title;
							articleStream >> author;

							articleStream.close();
							v.push_back(Article(title, author));
						}
					}
				}
			}
		}
		closedir (databaseDir);
	}
	return v;
}

Article MainDatabase::readArticle(int ngID, int articleID) const{
	Article a;

	DIR *databaseDir = nullptr;
	DIR *groupDir = nullptr;
	struct dirent *group = nullptr;
	struct dirent *dirEnt = nullptr;

	databaseDir = opendir(databaseRootPath.c_str());
	if(databaseDir != nullptr){
		while ((group = readdir (databaseDir)) != nullptr){

			string groupID(group->d_name);

			if(groupID != ".." && groupID != "." && stoi(groupID) == ngID){
				string groupDirString (databaseRootPath + "/" + groupID);
				groupDir = opendir(groupDirString.c_str());
				
				if(groupDir != nullptr){
					while (dirEnt = readdir (groupDir)){
						string entryName(dirEnt->d_name);

						if(entryName != "." && entryName != ".." && entryName != "GROUP_NAME" && stoi(entryName) == articleID){
							ifstream articleStream;
							articleStream.open(databaseRootPath + "/" + groupID + "/" + entryName);
							string title, author, text, line;
							articleStream >> title;
							articleStream >> author;

							while(!articleStream.eof()){
								getline(articleStream, line);
								text = text + line + "\n";
							}

							articleStream.close();
							a = Article(title, author, text);
						}
					}
				}
			}
		}
		closedir (databaseDir);
	}
	return a;
}

void MainDatabase::writeArticle(int groupIndex, Article& article){
	DIR *groupDir = nullptr;
	string groupPath = databaseRootPath + to_string(groupIndex);
	groupDir = opendir(groupPath.c_str());

	if(groupDir != nullptr){
		int freeArticleID = 0;
		string articlePath(groupPath + "/" + to_string(freeArticleID));
		while(opendir(articlePath.c_str()) != nullptr){
			++freeArticleID;
			articlePath = groupPath + "/" + to_string(freeArticleID);
		}

		ofstream nameFile;
		nameFile.open(articlePath);
		nameFile << article.title << endl;
		nameFile << article.author << endl;
		nameFile << article.text << endl;
		nameFile.close();
		closedir (groupDir);
	}
}

void MainDatabase::deleteArticle(int groupID, int articleID){
	DIR *groupDir = nullptr;
	string groupPath = databaseRootPath + to_string(groupID);
	groupDir = opendir(groupPath.c_str());

	if(groupDir != nullptr){
		string articlePath = groupPath + "/" + to_string(articleID);
		remove(articlePath.c_str());
	}
}

void MainDatabase::initDatabase(){
	if (opendir(databaseRootPath.c_str()) == nullptr){
		cout << "Creating root directory..." << endl;
		mkdir(databaseRootPath.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions
	}
}
