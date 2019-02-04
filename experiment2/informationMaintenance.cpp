#include<iostream>
#include<unistd.h>
#include<signal.h>
using namespace std;

bool test = false;
void waker(int sig){
    cout<<"Wake Up!";
    sleep(1);
    test = true;
}

int main(){
    signal(SIGALRM,waker);
    test = true;
    for( ; ; ){
        if(test){
            cout<<"Sleeping for 1 seconds";
            test = false;
            alarm(1);
        }
    }
    return 0;
}