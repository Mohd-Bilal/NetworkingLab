#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <unistd.h>
#define PORT 8080
#define MAX 80


void communicator(int connfd){
    char buffer[MAX];

    int n;
    for(;;){
        memset(buffer,0,MAX);
        read(connfd,buffer,sizeof(buffer));
        
        printf("Client says : %s \n",buffer);
        if(strcmp(buffer,"exit") == 0){
            printf("Server exiting..... \n");
            break;
        }
        memset(buffer,0,MAX);
        printf("Server says : ");
        scanf("%s",buffer);
        write(connfd,buffer,sizeof(buffer));
        


    }
}

int main(){
    struct sockaddr_in server,client;
    int socketfd,connfd;
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd == -1){
        printf("Socket creation failed !\n");
        exit(0);
    }    
    printf("Socket creation successful !\n");
    memset(&server,0,sizeof(server));

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = htonl(INADDR_ANY);
    server.sin_port = htons(PORT);

    if(bind(socketfd,(sockaddr *)&server,sizeof(server)) != 0){
        printf("Socket binding failed  !\n");
        exit(0);
    }
    printf("Socket binding successful !\n");
    if(listen(socketfd,5) < 0){
        printf("Listen failed !\n");
        exit(0);
    }
    printf("Server listening !\n");
    unsigned len = sizeof(client);
    connfd = accept(socketfd,(sockaddr *)&client,&len);
    if(connfd<0){
        printf("Accept failed ! \n");
        exit(0);
    }
    printf("Accept successful ! \n");
    communicator(connfd);
    close(socketfd);
    return 0;
}