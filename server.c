#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUFLEN 5000 //Max length of buffer
#define PORT 8888 //The port on which to send data

void die(char *s)
{
	perror(s);
	exit(1);
}

int main(){

   // Opening the file to write the data
   FILE *fptr;
   fptr = fopen("output.txt", "w");
   if(fptr == NULL)
   {
      printf("Error!");
      exit(1);
   }
   
   
	struct sockaddr_in si_me, si_other;
	int s, i, slen=sizeof(si_other);
	char buff[BUFLEN];
	char *token;
	//create a UDP socket
	if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
	  die("socket");
	}

	// zero out the structure 
	memset((char *) &si_me, 0, sizeof(si_me));
	si_me.sin_family = AF_INET;
	si_me.sin_port = htons(PORT);
	si_me.sin_addr.s_addr = htonl(INADDR_ANY);
    
    //bind socket to port
	if( bind(s , (struct sockaddr*)&si_me, sizeof(si_me) ) == -1)
	{
		die("bind");
	}
	while(1)
	{
       
		char seqNo[4];
		char packSize[4];
		char *isLastPkt = (char *)malloc(1);
		fflush(stdout);
		memset(&buff,'\0',sizeof(buff));
		memset(&seqNo,'\0',sizeof(seqNo));
		int temp2 = recvfrom(s, buff, BUFLEN, 0,(struct sockaddr*) &si_me,&slen);
		if (temp2 < 0)
		{   perror("problem in temp 2");
			exit (0);
		}
		// Start : Splitting the buff on the basis of delimiters "|"
		token = strtok(buff, "|");
		strcpy(seqNo,token);
		int seqNoInt = atoi(seqNo);
		token = strtok(NULL,"|");
		strcpy(packSize,token);
		token = strtok(NULL,"|");
		strcpy(isLastPkt,token);
		token = strtok(NULL,"|");
		token = strtok(NULL,"|");
		// End : Splitting the buff on the basis of delimiters "|"
		//Writting the data on the file using fptr.
		fprintf(fptr,"%s", token);
   		printf("---- RECEIVE PACKET %d length %s LAST PKT %s\n",seqNoInt,packSize,isLastPkt);
   		int bytesSent = sendto(s,seqNo,4,0,(struct sockaddr*)&si_me, sizeof(si_me));
   		if(bytesSent <0)perror("Error while sending ACK-");
   		printf("---- SEND ACK %d\n",seqNoInt);
   		
   		//If the packet have isLastPkt as 'Y' then close the collection.
   		if(*isLastPkt == 'Y')
   		{
   			printf("---- CLOSING CONNECTION\n");
   			exit(1);
   		}
   		

	}
fclose(fptr);
}