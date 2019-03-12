#include<sys/socket.h>
#include<netinet/in.h>
#include<string.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<netdb.h>
#include<arpa/inet.h>
#define PORT 8080
#define MAX 80
void communicator(int sockfd){
    char buffer[MAX];
    for(;;){
        memset(buffer,0,MAX);
        scanf("%s",buffer);
        write(sockfd,buffer,sizeof(buffer));
        memset(buffer,0,MAX);
        read(sockfd,buffer,sizeof(buffer));
        printf("Server says : %s",buffer);
        if(strcmp(buffer,"exit")== 0){
            printf("Client exiting \n");
            break;
        }
    }
}

int main(){
    struct sockaddr_in server;
    int sockfd;
    sockfd = socket(AF_INET,SOCK_STREAM,0);
    if(sockfd == -1){
        printf("Socket creation failed ! \n");
        exit(0);
    }
    printf("Socket creation successful ! \n");
    memset(&server,0,sizeof(server));
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_port = htons(PORT);

    if(connect(sockfd,(sockaddr *)&server,sizeof(server))!= 0){
        printf("Connection failed ! \n");
        exit(0);
    }
    printf("Connected to the server ! \n");
    communicator(sockfd);
    close(sockfd);


}