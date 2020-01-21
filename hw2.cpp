#include <iostream>
#include <string>
#include <unistd.h>
#include <sys/types.h>

using namespace std;
//in file descriptor
//fd0 =read
//fd1 = write
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