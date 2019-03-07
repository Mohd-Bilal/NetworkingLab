#include<thread>
// #include<iostream>
#include<stdio.h>
#include<unistd.h>
using namespace std;
int shared_resource = 0;
void addThread(int id){
    sleep(1);

    shared_resource++;
    if(id == 0){
    sleep(1);
        
        printf("This is an addition thread and was created by the child process,thread id is %ld \n",this_thread::get_id()); 
        printf("Shared resource :%d\n",shared_resource);
    }else{
        printf("This is an addition thread and was created by the parent process,thread id is %ld \n",this_thread::get_id());
        printf("Shared resource :%d \n",shared_resource);
    }
}
void multiplicationThread(int id){
    sleep(2);
    
    shared_resource*=2;

    if(id == 0){
    sleep(2);

        printf("This is a multiplicaion thread and was created by child process,thread id is %ld \n",this_thread::get_id());
        printf("Shared resource :%d \n",shared_resource);    
    }
    else{
        printf("This is a multiplication thread and was created by the parent process,thread id is %ld \n",this_thread::get_id());
        printf("Shared resource :%d \n",shared_resource);   
    }
    
}

int main(){
    int threadno = fork();
    thread thread1(addThread,threadno);
    
    thread thread2(multiplicationThread,threadno);
    thread1.join();
    thread2.join();
    return 0;
}