#include "user_io.h"
#include <string>
#include <iostream>
using namespace std;

string UserIO::getInput(){
	string input;
	cin >> input;
	return input;
}

void UserIO::print(string output){
	cout << output << endl;
}