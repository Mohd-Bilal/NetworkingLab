////////////////////////////////////////
//                                    //
//Server For Multiuser chat using tcp //
//                                    //
////////////////////////////////////////
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<pthread.h>
#include<vector>
#include<string.h>
#define PORT 8080
#define MAX 1024
using namespace std;
vector<int> socketList;

void *userCallBack( void * socketfd){
    char buffer[MAX];
    char serverMessage[] = "Welcome to MUCS! \nEnjoy your stay !\n";
    for(;;){
    int n = read((long)socketfd,buffer,sizeof(buffer));
    printf("Client #%d: %s\n",socketfd,buffer);
    for(int i = 0;i<socketList.size();i++){
        if(socketList[i] != (long)socketfd){
            write(socketList[i],buffer,sizeof(buffer));
        }
    }
    if(strcmp(buffer,"exit") == 0)
        break;
    }
    printf("Client #%d exiting......\n",(long)socketfd);
    pthread_exit(NULL);
}

int main(){
    int socketfd,temp;
    struct sockaddr_in server,client;
    memset(&server,0,sizeof(server));
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd <0){
        printf("Socket creation failed !\n");
        exit(0);
    }
    printf("Socket  creation successful !\n");

    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    if(bind(socketfd,(sockaddr *)&server,sizeof(server))!=0){
        printf("Socket binding failed !\n");
        exit(0);
    }
    printf("Socket binding successful\n");
    if(listen(socketfd,5) <0){
        printf("Listening failed !\n");
        exit(0);
    }
    printf("Listening successful !\n");
    for(;;){
    unsigned len = sizeof(client);
    temp = accept(socketfd,(sockaddr *)&client,(socklen_t *)&len);
    if(temp < 0){
        printf("Client connection failed !\n");
    }else{
        pthread_t userThread;
        pthread_create(&userThread,NULL,userCallBack,(void *)temp);
        socketList.push_back(temp);
        printf("Client connected !\n");
        temp = -1;
    }
    }
    close(socketfd);
    
    return 0;
}