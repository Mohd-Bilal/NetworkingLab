#include<thread>
#include<iostream>
#include<unistd.h>
using namespace std;
void threadcb(int id){
    if(id == 0)
        cout<<"This thread was created by child process and thread id is \n"<<
        this_thread::get_id()<<"\n";
    else
        cout<<"This thread was created by the parent process and thread id is 
        \n"<<this_thread::get_id()<<"\n";
    
}

int main(){
    int threadno = fork();
    thread thread1(threadcb,threadno);
    thread thread2(threadcb,threadno);
    thread1.join();
    thread2.join();
    return 0;
}