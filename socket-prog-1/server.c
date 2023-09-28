#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>
#define SIZE 1024

// Just change this function
// check if the file requested by client is present or not
// if present send yes or no
// wait for client request of word# and start sending word by word


void write_file(int sockfd){   // sockfd of client
	printf("\nHey from server");


	int sentbytes;
	int recebytes;
	char fileName[50];
	char fileData[200];
	char wordArr[1024];
	char buffer[250];
	
	recebytes = recv(sockfd,buffer,sizeof(buffer),0);
	if(recebytes == -1){
		// is reception fails
		printf("\nNo file name found at server");
		close(sockfd);
		exit(0);	
	}

	printf("\nFile requested is : %s",buffer);
	
	
	if (access(buffer, F_OK) == 0) {
		printf("\nFile exists");
		strcpy(fileName,buffer);		
		strcpy(buffer,"File exists");
		sentbytes = send(sockfd,buffer,sizeof(buffer),0);	// file not found
		if(sentbytes == -1){
			close(sockfd);
			printf("\nFile exists message failed");
			exit(0);	
		}
	} else {
	    	strcpy(buffer,"File Not found");
		sentbytes = send(sockfd,buffer,sizeof(buffer),0);	// file not found
		if(sentbytes == -1){
			close(sockfd);
			printf("\nError sending yes no at server");
			exit(0);	
		}
		printf("\nFile does not exist at server");
		close(sockfd);
		exit(0);
	}

	recebytes = recv(sockfd,buffer,sizeof(buffer),0);
	if(recebytes == -1){
		// is reception fails
		printf("\nWord 0 request failed");
		close(sockfd);
		exit(0);	
	}

	printf("%s",buffer); // must print word_0

	FILE *fp;
	
	fp = fopen(fileName, "r");
	
	if(fp == NULL){	
		printf("error opening file");
		close(sockfd);
		exit(0);
	}

	while (fscanf(fp, " %1023s", wordArr) == 1) {		// longest word is 1023
		strcpy(buffer,wordArr);
		printf("\nwords : %s",buffer);


		sentbytes = send(sockfd,buffer,sizeof(buffer),0);	// file not found
		if(sentbytes == -1){
			close(sockfd);
			printf("\nError sending words to client");
			close(sockfd);
			exit(0);	
		}

		recebytes = recv(sockfd,buffer,sizeof(buffer),0);
		if(recebytes == -1){
			// is reception fails
			printf("\nNo word request from client");
			close(sockfd);
			exit(0);	
		}
	
		printf("\nwords : %s",buffer);

	}
	
	strcpy(buffer,"EOF");
	sentbytes = send(sockfd,buffer,sizeof(buffer),0);	// file not found
	if(sentbytes == -1){
		close(sockfd);
		printf("\nError sending words to client");
		exit(0);	
	}
	
	fclose(fp);


}
 
int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
 
  int sockfd, new_sock;
  struct sockaddr_in server_addr, new_addr;
  socklen_t addr_size;
  char buffer[SIZE];
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e < 0) {
    perror("[-]Error in bind");
    exit(1);
  }
  printf("[+]Binding successfull.\n");
 
  if(listen(sockfd, 10) == 0){
 printf("[+]Listening....\n");
 }else{
 perror("[-]Error in listening");
    exit(1);
 }
 
  addr_size = sizeof(new_addr);
  new_sock = accept(sockfd, (struct sockaddr*)&new_addr, &addr_size);

  // sending file here word by word
  write_file(new_sock);				

		
  printf("\n[+]Data written in the file successfully.\n");
  close(sockfd);
close(new_sock);
  return 0;
}
