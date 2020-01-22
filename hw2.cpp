#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>
#include <vector>
#include <cstring>

using namespace std;



const int PIPE_READ = 0;
const int PIPE_WRITE = 1;
int fd[9][2];
int childNum = -1;
int cpid;
vector<vector<string>> tokens;

int main(){
	//cout << "program started" << endl;
	tokens.push_back(vector<string>());
	tokens.push_back(vector<string>());
	tokens.at(0).push_back("ls");
	tokens.at(0).push_back("-laF");
	tokens.at(0).push_back("/");
	tokens.at(1).push_back("tr");
	tokens.at(1).push_back("a-z");
	tokens.at(1).push_back("A-Z");
	//cout << "vectors filled" << endl;
	

// if (fork() == 0) {
//   dup2(fds[PIPE_WRITE], PIPE_WRITE);
//   close(fds[PIPE_READ]);
//   close(fds[PIPE_WRITE]);
// }

	for (int i = 0; i < (int)tokens.size() - 1; i++)
		pipe(fd[i]);

	for (int j = 0; j < (int)tokens.size(); j++){
		cpid = fork();
		if (cpid == 0){
			childNum = j;
			//cout << "childNum:" << childNum;
			break;
		}
	}

	//cout << "Pipes Made"<< endl;


// while (i < token.size){
//     cpid = fork()
//     if(cpid == 0)
//         break;
//     i++;
// }

	if (childNum == -1)
	{
		cout << "Parent sits here" << endl;
		//for (int j = 0; j < (int)tokens.size()-1; j++){
		//close(fd[j][PIPE_READ]);
		//close(fd[j][PIPE_WRITE]);
	}

	//}
	else{
		/*for (int j = 0; j < (int)tokens.size()-1; j++){
			if(j == childNum)
				close(fd[j][PIPE_READ]);
			if(j == childNum - 1 && childNum > 0)
				close(fd[j][PIPE_WRITE]);
			else
			{
				close(fd[j][PIPE_READ]);
				close(fd[j][PIPE_WRITE]);
			}
		}*/
		if(childNum == 0) {
			close(fd[0][0]);
			dup2(fd[0][1], 0);
			//getline(cin, userInput);
			//cout << userInput << " FromChild0";
		} else {
			close(fd[0][1]);
			dup2(fd[0][0], 1);
			//getline(cin, userInput);
			//cout << userInput << " FromChild1";
		}

		//cout << "vectors filled"<< endl;
		/*if(childNum < (int)tokens.size() - 1)
			dup2(fd[childNum][PIPE_WRITE],PIPE_WRITE);

		if(childNum > 0)
			dup2(fd[childNum-1][PIPE_READ],PIPE_READ);*/
		//cout << "Pipes Linked"<< endl;
    //char buf[50][100];
    // for (int i = 0; i < (int)tokens.at(childNum).size(); ++i)
    // {
    //     //strcpy(buf[i],tokens.at(childNum).at(i));
    // 	strcpy(buf[i],(char*)test);
    // }



		char* args[50];

		for (int i = 0; i < (int)tokens.at(childNum).size(); ++i)
		{
			args[i] = (char*)(tokens.at(childNum).at(i).c_str());
		}

		for(int i = 0; i < (int)tokens.at(childNum).size();i++){
			//cout << args[i] << endl;
		}

		args[tokens.at(childNum).size()] = (char*)NULL;
		//cout << "args argd"<< endl;


		execvp(args[0],args);

	}	

}


