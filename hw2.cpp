#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <vector>

using namespace std;
//in file descriptor
//fd0 =read
//fd1 = write

void getCommands(string commandList, vector<string>& commands) {
	int lastPipe = 0;
	for(int i = 0; i < commandList.length(); i++) {
		if(commandList[i] == '|') {
			commands.push_back(commandList.substr(lastPipe, i - lastPipe));
			lastPipe = i + 1;
		}
	}
	commands.push_back(commandList.substr(lastPipe, commandList.length() - lastPipe));
}

int main(){
    int array[2]; //file descriptors
    pipe(array);
    int pid = fork();
    string userInput;

    if (pid == 0){//child
        close(array[1]);// close write end in the child
        dup2(array[0], 0);
        getline(cin, userInput);
        cout << userInput << " From Child";
        close(array[1]);
    }else{//parent
        close(array[0]);//closing read 
        dup2(array[1], 1);//whenever you write to 1 actually write into pipe
        getline(cin, userInput);
        cout << userInput<< " From Parent";
        close(array[0]);
    }

}
