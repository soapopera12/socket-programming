#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#define SIZE 1024


// specify which file it wants
// if server has that file send yes or no
// if yes start recieving word by word 
void send_file(int sockfd){  // sockfd of client itself
	printf("Hey from client");
	
	int wordCount = 0;
	int sentbytes;
	int recebytes;
	char wordConversion[100];
	char wordRequested[100];
	char wordRecieved[100];
	char buffer[250];
	printf("\nEnter file name : ");
	scanf("%s",buffer);

	sentbytes = send(sockfd,buffer,sizeof(buffer),0);	// sending bytes and reading how many bytes were sent
	if(sentbytes == -1){
		// if sending fails
		close(sockfd);
		printf("Failed sending file name");
		close(sockfd);
		exit(0);	
	}
	
	recebytes = recv(sockfd,buffer,sizeof(buffer),0);		// recieving yes or no and storing in buffer
	if(recebytes == -1){
		// is reception fails
		close(sockfd);
		printf("failed reception");
		close(sockfd);
		exit(0);
	}

	// buffer probably has file name yes or no
	if(strcmp(buffer, "File Not found") == 0){
		printf("\n%s",buffer);
		printf("\nFile was not found");
		close(sockfd);
		exit(0);
	}else{
		printf("\nFile found");		
	}


	// make a new file
	//strcpy(wordRequested,"Word#");
	sprintf(wordConversion, "%d", wordCount);
	FILE *fp;
	fp = fopen("clientFile.txt", "w");		// created a new file
	
	if (fp != NULL) {
		printf("\nFile opening successfull");
	} else {
		printf("\nFile creation failed");
	}
	
	
	// start req packets
	while(1){
		strcpy(wordRequested,"Word#");
		strcat(wordRequested,wordConversion);
		strcpy(buffer,wordRequested);	// keeping req in buffer
		printf("\n%s",buffer);


		sentbytes = send(sockfd,buffer,sizeof(buffer),0);	// sending bytes and reading how many bytes were sent
		if(sentbytes == -1){
			// if sending fails
			close(sockfd);
			printf("\nFailed sending buffer data at client");
			exit(0);
		}


		recebytes = recv(sockfd,buffer,sizeof(buffer),0);		// recieving yes or no and storing in buffer		
		if(recebytes == -1){
			// is reception fails
			close(sockfd);
			printf("\nfailed reception data at client");
			exit(0);	
		}
		printf("\n%s",buffer);
		fprintf(fp,"%s\n",buffer);

		if(strcmp(buffer,"EOF") == 0){
			printf("\nReached EOF");
			break;
		}

		wordCount++;
		sprintf(wordConversion, "%d", wordCount);
	}
	
	fclose(fp);

}
 


int main(){
  char *ip = "127.0.0.1";
  int port = 8080;
  int e;
 
  int sockfd;
  struct sockaddr_in server_addr;
  //FILE *fp;
  //char *filename = "send.txt";	// file that i want to request
 
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if(sockfd < 0) {
    perror("[-]Error in socket");
    exit(1);
  }
  printf("[+]Server socket created successfully.\n");
 
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = port;
  server_addr.sin_addr.s_addr = inet_addr(ip);
 
  e = connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
  if(e == -1) {
    perror("[-]Error in socket");
    exit(1);
  }
 printf("[+]Connected to Server.\n");
 
  //fp = fopen(filename, "r");
  //if (fp == NULL) {
   // perror("[-]Error in reading file.");
    //exit(1);
  //}
 
  // call this method in a loop for word by word till EOF

  send_file(sockfd);
  printf("\n[+]File data sent successfully.\n");
 
  printf("\n[+]Closing the connection.\n");
  close(sockfd);
 
  return 0;
}
