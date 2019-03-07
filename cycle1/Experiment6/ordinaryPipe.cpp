#include<stdio.h> 
#include<unistd.h>
#include<stdlib.h> 
#include<sys/wait.h>
#define MSGSIZE 16 
char msg[][MSGSIZE] = {"hello, world #1","hello, world #2","hello, world #3"}; 

int main() 
{ 
	char inbuf[MSGSIZE]; 
	int p[2], i,pid;

	if (pipe(p) < 0) 
		exit(1); 
	if((pid = fork()) > 0){
		for(i = 0;i<3;i++){
			printf("Writing message %s to pipe ...\n",msg[i],i);
			write(p[1],msg[i],MSGSIZE);
		}
		wait(NULL);
	}
	else{
		for (i = 0; i < 3; i++) { 
			read(p[0], inbuf, MSGSIZE); 
			printf("The parent says % s\n", inbuf); 
		} 
		printf("Finished reading");
		exit(2);
	}
	return 0; 
} 
