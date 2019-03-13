////////////////////////////////////////////////
//                                            //
//     Client for MultiUserChat Server        //
//                                            //
////////////////////////////////////////////////
#include<sys/socket.h>
#include<sys/types.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080
#define MAX 1024
int main(){
    int socketfd;
    struct sockaddr_in server;
    memset(&server,0,sizeof(server));
    socketfd = socket(AF_INET,SOCK_STREAM,0);
    if(socketfd < 0){
        printf("Socket creation failed !\n");
        exit(0);
    }
    printf("Socket creation successful !\n");

    server.sin_addr.s_addr = inet_addr("127.0.0.1");
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);

    if(connect(socketfd,(sockaddr *)&server,sizeof(server))!= 0){
        printf("Connection failed \n");
        exit(0);
    }
    printf("Connection successful !\n");
    char buffer[MAX];
    for(;;){
    scanf("%s",buffer);
    
    write(socketfd,buffer,sizeof(buffer));
    printf("Data send to server!\n");
    if(strcmp(buffer,"exit") == 0){
        printf("Client #%d exiting...\n",socketfd);
        break;
    }
    read(socketfd,buffer,sizeof(buffer));
    printf("Server says : %s\n",buffer);

    }
    close(socketfd);
    return 0;
}