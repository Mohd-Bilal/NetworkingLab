#include<arpa/inet.h>
#include<sys/socket.h>
#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<unistd.h>
#include<sys/types.h>
#include<ctime>
using namespace std;

#define PORT 8080
#define MAXLINE 1024 

void communicator(int socketfd){
    char inp_buffer[MAXLINE],out_buffer[MAXLINE];
    struct sockaddr_in client;
    int n = 0,len;
    for(;;){
    n = recvfrom(socketfd,inp_buffer,sizeof(inp_buffer),MSG_WAITALL,(sockaddr *)&client,(socklen_t *)&len);
    inp_buffer[n] = '\0';
    printf("Client :%s\n",inp_buffer);

    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(out_buffer,sizeof(out_buffer),"%d-%m-%Y %H:%M:%S",timeinfo);

    if(strcmp(inp_buffer,"now") == 0){
        sendto(socketfd,out_buffer,strlen(out_buffer),MSG_CONFIRM,(sockaddr *)&client,len);
        printf("Time sent to client \n");
    }
    }
}

int main(){
    int socketfd;
    struct sockaddr_in server;
    socketfd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketfd < 0){
        printf("Socket creation failed !\n");
        exit(0);
    }
    printf("Socket creation successful !\n");
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);
    server.sin_family = AF_INET;
    if(bind(socketfd,(sockaddr *)&server,sizeof(server))<0){
        printf("Socket binding failed !\n");
        exit(0);
    }
    printf("Socket binding successful !\n");
    communicator(socketfd);

    return 0;
}