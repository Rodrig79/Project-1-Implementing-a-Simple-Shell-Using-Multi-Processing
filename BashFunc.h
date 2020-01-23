#ifndef BASHFUNC_H
#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <vector>

using namespace std;

/* 
	Given a list of commands seperated by pipes, pushes each 
	command onto the given vector
*/

void getCommands(string commandList, vector<string>& commands);

/*
	Given a vector of commands pushes each token of each 
	command onto a vector of vectors
*/

void getTokens(vector<string>& commands, vector<vector<string>>& tokens);

/*
	creates the number of pipes specified using the corresponding file descriptors
*/

void createPipes(int fd[][2], int numPipes);

/*
	creates the number of children specified by numChildren, returns a number
	between 0 and numChildren corresponding to each child created
	the parent process returns -1
	May cause an error if a new child process fails to be created
*/

int createChildren(int numChildren);

/*
	closes all file descriptors not needed by a specified child number
	children read from the file descriptor of 1 - childNum and write to the
	file descriptor childNum. The parent's childNum will close all file descriptors
*/

void closePipes(int childNum, int fd[][2], int numPipes);

/*
	connects each childs input and output to the corresponding pipe it uses.
	See description of closePipes for more info.
	May cause an error if input/output cannot be duplicated
*/

void linkPipes(int childNum, int fd[][2], int numPipes);

/*
	executes the program denoted by args at the specified child number
	May cause an error if the arguments specify a program that doesn't exist
	or if something else goes wrong when executing the program
*/

void execute(vector<vector<string>>& arguments, int childNum);

#endif
