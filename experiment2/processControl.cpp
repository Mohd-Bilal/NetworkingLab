#include<stdlib.h>
#include<unistd.h>
#include<iostream>
#include<sys/wait.h>
using namespace std;


int main(){
    int i = 0;
    pid_t pid = fork();
    if(pid == 0){
        cout<<"Child Process executing.....\n";
        exit(0);
    }else if(pid>0){
        cout<<"Parent process executing...\n";
        pid_t child = wait(NULL);
        if(child == pid){
            cout<<"Child process died ...\n";
        }
        cout<<"Parent process finished...\n";

              
    }else{
        cout<<"Error";
        exit(1);
    }


    return 0;
}