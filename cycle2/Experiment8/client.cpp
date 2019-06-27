
#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <string.h> 
#include <sys/types.h> 
#include <sys/socket.h> 
#include <arpa/inet.h> 
#include <netinet/in.h> 
#define PORT	 8080 
#define MAXLINE 1024 

void communicator(int sockfd){
    int n, len; 
	struct sockaddr_in	 servaddr,cliaddr; 
    char buffer[MAXLINE]; 
    char clientMessage[MAXLINE];
    memset(&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(PORT); 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
    for(;;){
        scanf("%s",clientMessage);
	    sendto(sockfd, (const char *)clientMessage, strlen(clientMessage), MSG_CONFIRM, (const struct sockaddr *) &servaddr,sizeof(servaddr)); 
	    printf("Client message sent.\n"); 
		if(strcmp(clientMessage,"exit") == 0){
			printf("Client exiting \n");
			exit(0);
		}
	    n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, (struct sockaddr *) &servaddr,(socklen_t *)&len); 
	    buffer[n] = '\0'; 
	    printf("Server : %s\n", buffer); 
		
    }
}

int main() { 
	int sockfd; 	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		perror("socket creation failed"); 
		exit(EXIT_FAILURE); 
	} 
    communicator(sockfd);
	close(sockfd); 
	return 0; 
} 
