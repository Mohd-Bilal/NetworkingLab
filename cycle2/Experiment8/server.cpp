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
    int len, n; 
    struct sockaddr_in  cliaddr;
    memset(&cliaddr, 0, sizeof(cliaddr)); 
    char buffer[MAXLINE],serverMessage[MAXLINE]; 
    for(;;){
	memset(buffer,0,sizeof(buffer));
	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, ( struct sockaddr *) &cliaddr, (socklen_t *)&len); 
	printf("Client : %s\n", buffer); 
	if(strcmp(buffer,"exit") == 0){
		printf("Server exiting \n");
		exit(0);
	}
	memset(serverMessage,0,sizeof(serverMessage));

    scanf("%s",serverMessage);
	sendto(sockfd, (char *)&serverMessage, strlen(serverMessage), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len); 
	printf("Client message sent.\n");
    }
}
 
int main() { 
	int sockfd; 
	struct sockaddr_in servaddr; 
	
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) { 
		printf("socket creation failed"); 
		exit(0); 
	} 
	
	memset(&servaddr, 0, sizeof(servaddr)); 
	

	servaddr.sin_family = AF_INET; 
	servaddr.sin_addr.s_addr = INADDR_ANY; 
	servaddr.sin_port = htons(PORT); 

	if ( bind(sockfd, (const struct sockaddr *)&servaddr, 
			sizeof(servaddr)) < 0 ) 
	{ 
		printf("bind failed"); 
		exit(0); 
	} 
	
	communicator(sockfd);
	
	return 0; 
} 
