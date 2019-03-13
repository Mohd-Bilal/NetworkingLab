#include<sys/socket.h>
#include<sys/types.h>
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<string.h>

#define PORT 8080
#define MAX 1024

void communicator(int socketfd){
    char inp_buffer[MAX],out_buffer[MAX];
    struct sockaddr_in server;

    server.sin_family = AF_INET;
    server.sin_addr.s_addr = INADDR_ANY;
    server.sin_port = htons(PORT);

    strcpy(out_buffer,"now");
    sendto(socketfd,out_buffer,strlen(out_buffer),MSG_CONFIRM,(sockaddr *)&server,sizeof(server));
    int n,len;
    memset(inp_buffer,0,sizeof(inp_buffer));
    n = recvfrom(socketfd,inp_buffer,MAX,MSG_WAITALL,(sockaddr *)&server,(socklen_t *)&len);
    printf("Server: %s\n",inp_buffer);

}
int main(){
    int socketfd;
    socketfd = socket(AF_INET,SOCK_DGRAM,0);
    if(socketfd<0){
        printf("Socket creation failed !\n");
        exit(0);
    }
    printf("Socket creation successful !\n");
    communicator(socketfd);
    return 0;
}