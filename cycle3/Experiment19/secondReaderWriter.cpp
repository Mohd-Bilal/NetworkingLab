#include<stdio.h>
#include<pthread.h>
#include<semaphore.h>
#include<cstdlib>

using namespace std;

sem_t resource;
sem_t rmutex;
sem_t wmutex;
sem_t readTry ;
int readcount =0;
int writecount =0;

void *ReaderCallBack(int *ID){
    sem_wait(readTry);
    sem_wait(rmutex);
    readcount++;
    if(readcount == 1)
        sem_wait(resource);
    sem_post(rmutex);
    sem_post(readTry);
    //CRITICAL SECTION

    sem_wait(rmutex);
    readcount--;
    if(readcount == 0)
        sem_post(resource);
    sem_post(rmutex);    
}
void *WriterCallBack(int *ID){
    sem_wait(wmutex);
    writecount++;
    if(writecount == 1)
        sem_wait(readTry)
    sem_post(wmutex);
    sem_wait(resource);
    //CRITICAL SECTION
    sem_post(resource);    
    sem_wait(wmutex);
    writecount--;
    if(writecount == 0)
        sem_post(readTry);
    sem_post(wmutex);

}
int main(){
    sem_init(&resource,0,1);
    sem_init(&rmutex,0,1);
    sem_init(&wmutex,0,1);
    sem_init(&readTry,0,1);

    return 0;
}