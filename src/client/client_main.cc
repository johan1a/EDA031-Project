#include "user_io.h"
#include "client_command_handler.h"

using namespace std;

int main(){
	bool isConnected = true;
	UserIO userIO;
	ClientCommandHandler cmdHandler;

	string input, output;
	while (isConnected){
		input = userIO.getInput();
		output = input;
		userIO.print(output);
		isConnected = false;
	}
}