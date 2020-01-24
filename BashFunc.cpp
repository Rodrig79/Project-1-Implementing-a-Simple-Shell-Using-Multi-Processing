#include "BashFunc.h"

int PIPE_READ = 0;
int PIPE_WRITE = 1;

void getCommands(string commandList, vector<string>& commands) {
	int lastPipe = 0;
	int inQuote = false;
	for(int i = 0; i < commandList.length(); i++) {
		if(commandList[i] == '|' && !inQuote) {
			if(lastPipe != i) {
				commands.push_back(commandList.substr(lastPipe, i - lastPipe));
			}
			lastPipe = i + 1;
		} else if (commandList[i] == '\"' || commandList[i] == '\'') {
			inQuote = !inQuote;
		}
	}
	commands.push_back(commandList.substr(lastPipe, commandList.length() - lastPipe));
}

void getTokens(vector<string>& commands, vector<vector<string>>& tokens) {
	int lastCommand = 0;
	int inQuote = false;
	
	for(string command : commands) {
		tokens.push_back(vector<string>());
		lastCommand = 0;
		inQuote = false;
		for(int i = 0; i < command.length(); i++) {
			if((command[i] == ' ' || command[i] == 9) && !inQuote) {
				if(lastCommand != i) {
					tokens.back().push_back(command.substr(lastCommand, i - lastCommand));
				}
				lastCommand = i + 1;
			} else if (command[i] == '\"' || command[i] == '\'') {
				if(inQuote) {
					tokens.back().push_back(command.substr(lastCommand, i - lastCommand));
				}
				lastCommand = i + 1;
				inQuote = !inQuote;
			}
		}
		if(lastCommand != command.length()) {
			tokens.back().push_back(command.substr(lastCommand, command.length() - lastCommand));
		}
	}
}

void createPipes(int fd[][2], int numPipes) {
	for(int i = 0; i < numPipes; i++) {
		if(pipe(fd[i]) == -1) {
			perror(string("error creating pipes").c_str())
		}
	}
}

int createChildren(int numChildren) {
	int childNum = -1;
	for(int i = 0; i < numChildren; i++) {
		int cpid  = fork();
		if(cpid == -1) {
			perror(string("error forking").c_str())
		} else if(cpid == 0) {
			childNum = i;
			break;
		}
	}
	return childNum;
}

void closePipes(int childNum, int fd[][2], int numPipes) {
	for(int i = 0; i < numPipes; i++) {
		if(childNum == i) {
			close(fd[i][PIPE_READ]);
		} else if (childNum == i + 1 && childNum > 0) {
			close(fd[i][PIPE_WRITE]);
		} else {
			close(fd[i][PIPE_READ]);
			close(fd[i][PIPE_WRITE]);
		}
	}
	
}

void linkPipes(int childNum, int fd[][2], int numPipes) {
	if(childNum < numPipes) {
		if(dup2(fd[childNum][PIPE_WRITE], PIPE_WRITE) == -1) {
			perror(string("could not duplicate file descriptor to pipe").c_str());
		}
	}
	if(childNum > 0) {
		if(dup2(fd[childNum - 1][PIPE_READ], PIPE_READ) == -1) {
			perror(string("could not duplicate file descriptor to pipe").c_str());
		}
	}
}

void execute(vector<vector<string>>& arguments, int childNum) {
		char* args[50];
		for(int i = 0; i < arguments.at(childNum).size(); i++)
			args[i] = (char*)(arguments.at(childNum).at(i).c_str());
		args[arguments.at(childNum).size()] = (char*)NULL;
		if(execvp(args[0], args) == -1) {
			perror(args[0]);
			exit(1);
		}
}
