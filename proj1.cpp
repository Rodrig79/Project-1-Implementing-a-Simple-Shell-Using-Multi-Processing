#include "BashFunc.h"


int main(){
	string input;
	int fd[9][2];
	int childNum;
	vector<string> commands;
	vector<vector<string>> tokens;
	
	getline(cin, input);
	getCommands(input, commands);
	getTokens(commands, tokens);
	createPipes(fd, tokens.size() - 1);
	childNum = createChildren(tokens.size());
	if(childNum >= 0) {
		closePipes(childNum, fd, tokens.size() - 1);
		linkPipes(childNum, fd, tokens.size() - 1);
		execute(tokens, childNum);
	} else {
		closePipes(childNum, fd, tokens.size() - 1);
	}
}
