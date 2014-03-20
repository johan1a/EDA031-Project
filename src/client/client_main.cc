#include "userio.h"
#include "clientcommandhandler.h"

using namespace std;

int main(){
	bool isConnected = true;
	UserIO userIO;
	ClientCommandHandler cmdHandler;

	string input, output;
	while (isConnected){
		input = userIO.getInput();
		output = cmdHandler.execute(input);
		userIO.print(output);
		isConnected = false;
	}
}