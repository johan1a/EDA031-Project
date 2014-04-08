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
	listArticlesFor(0);
}

vector<NewsGroup> MainDatabase::listNewsGroups() const{
	vector<NewsGroup> v;

	DIR *databaseDir = nullptr;
	DIR *groupDir = nullptr;
	struct dirent *group = nullptr;
	struct dirent *dirEnt = nullptr;

	databaseDir = opendir(databaseRoot.c_str());
	if(databaseDir != nullptr){
		while ((group = readdir (databaseDir)) != nullptr){

			string groupID(group->d_name);
			if(groupID != "." && groupID != ".."){
				string groupDirString (databaseRoot + "/" + groupID);
				groupDir = opendir(groupDirString.c_str());
				
				if(groupDir != nullptr){
					while (dirEnt = readdir (groupDir)){
						string entryName(dirEnt->d_name);

						if(entryName == "GROUP_NAME"){
							ifstream articleStream;
							articleStream.open(databaseRoot + "/" + groupID + "/" + entryName);
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

}

void MainDatabase::deleteNewsGroup(int){
	string s("");
}

vector<Article> MainDatabase::listArticlesFor(int ngID) const{
	vector<Article> v;

	DIR *databaseDir = nullptr;
	DIR *groupDir = nullptr;
	struct dirent *group = nullptr;
	struct dirent *dirEnt = nullptr;

	databaseDir = opendir(databaseRoot.c_str());
	if(databaseDir != nullptr){
		while ((group = readdir (databaseDir)) != nullptr){

			string groupID(group->d_name);

			if(groupID != ".." && groupID != "." && stoi(groupID) == ngID){
				string groupDirString (databaseRoot + "/" + groupID);
				groupDir = opendir(groupDirString.c_str());
				
				if(groupDir != nullptr){
					while (dirEnt = readdir (groupDir)){
						string entryName(dirEnt->d_name);

						if(entryName != "." && entryName != ".." && entryName != "GROUP_NAME"){
							ifstream articleStream;
							articleStream.open(databaseRoot + "/" + groupID + "/" + entryName);
							string title, author, text, line;
							articleStream >> title;
							articleStream >> author;

							while(!articleStream.eof()){
								getline(articleStream, line);
								text = text + line + "\n";
							}

							articleStream.close();
							v.push_back(Article(title, author, text));
						}
					}
				}
			}
		}
		closedir (databaseDir);
	}
	return v;
}

Article MainDatabase::readArticle(int  articleName, int ngName) const{

}

void MainDatabase::writeArticle(int groupIndex, Article& article){
	string s("");
}

void MainDatabase::deleteArticle(int articleName, int ngName){
	string s("");
}

void MainDatabase::initDatabase(){
	if (opendir(databaseRoot.c_str()) == nullptr){
		cout << "Creating root directory..." << endl;
		mkdir(databaseRoot.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH); // TODO mega unstrict permissions
	}
}
