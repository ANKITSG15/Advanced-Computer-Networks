#include<stdio.h> //printf
#include<string.h> //memset
#include<stdlib.h> //exit(0);
#include<arpa/inet.h>
#include<sys/socket.h>
#define BUFLEN 512 //Max length of buffer
#include <stdbool.h>

void die(char *s)
{
perror(s);
exit(1);
}

int main(int argc, char *argv[])
{
int inPktSize = atoi(argv[4]);// converting string to Integer.
//printf("InputPacketSize = %d\n",inPktSize );
int port = atoi(argv[2]);
struct sockaddr_in si_other;
int s, i, slen=sizeof(si_other);
int bytesSent;
int offset =0;
char *buffer;
char *bufferAck;
long fileLen;

//Creating Socket
if ((s=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
{
die("socket");
}

memset((char *) &si_other, 0, sizeof(si_other));
//Defining Protocal Family, IP and Port.
si_other.sin_family = AF_INET;
si_other.sin_port = htons(port);
si_other.sin_addr.s_addr = inet_addr(argv[1]);
int c = connect (s,(struct sockaddr *) &si_other, sizeof(si_other));

/* Open the file that we wish to transfer */
FILE *fp = fopen(argv[3],"rb");
if(fp==NULL)
{
perror("Erro while opening file");
}

fseek(fp,0,SEEK_END);
fileLen=ftell(fp);
fseek(fp,0,SEEK_SET);
//buffer : to store file data and bufferAck : to store acknowledgement number. 
buffer = (char *)malloc(fileLen+1);
bufferAck = (char *)malloc(4);

if(!buffer)
{
printf("Memory not allocated for bufffering at client end");
exit(0);
}
else{

	fread(buffer,fileLen,1,fp);
	fclose(fp);
}

int windowSize = atoi(argv[5]);// converting string to Integer 
int localWindowSize = windowSize;
int totalAck = (fileLen/inPktSize)+((fileLen%inPktSize)!=0); // Number of Ack or Packet to send


//Structing the packet as SeqNo|PktSize|IsLast|PktType|Payload : Starts
char *parm3PktSize =(char *)malloc(4);
char *parm1PktType = (char *)malloc(2);
char *parm2IsLastPkt = (char *) malloc(2);
char *parm4SeqNum = (char *) malloc(4);
char *parm5Delimit = (char *)malloc(1);
sprintf(parm5Delimit,"%s","|");
char *parm6Delimit = (char *)malloc(1);
sprintf(parm6Delimit,"%s","|");
sprintf(parm4SeqNum,"%d",5000);
sprintf(parm2IsLastPkt,"%s","|N");
sprintf(parm1PktType,"%s","D|");
sprintf(parm3PktSize,"%d",inPktSize);
int seqNumber = 0;
//Structing the packet as SeqNo|PktSize|IsLast|PktType|Payload : Ends
while(1){
	
	char *payloadPktSent =(char *) malloc(inPktSize);
	char *finalPktToSent = (char *) malloc(inPktSize+14);
	
		if(fileLen <=inPktSize)// for Last Packet or if file size is less than packet size then only one packet will be sent
			{
				inPktSize=fileLen;
				sprintf(parm3PktSize,"%ld",fileLen);
				sprintf(parm2IsLastPkt,"%s","|Y");
			}
		for(int i=0;i<windowSize;i++)
		{
			for(int i=offset;i<inPktSize;i++)
		{
			payloadPktSent[i] = buffer[i];
		}
		if(fileLen <=inPktSize)// for Last Packet or if file size is less than packet size then only one packet will be sent
			{
				inPktSize=fileLen;
				sprintf(parm3PktSize,"%ld",fileLen);
				sprintf(parm2IsLastPkt,"%s","|Y");
					
			}	
		payloadPktSent[inPktSize] ='\0';
		sprintf(parm4SeqNum,"%d",seqNumber);
		seqNumber++;
		sprintf(finalPktToSent,"%s%s%s%s%s%s%s",parm4SeqNum,parm5Delimit,parm3PktSize,parm2IsLastPkt,parm6Delimit,parm1PktType,payloadPktSent);	
		buffer = buffer + inPktSize;
		bytesSent = sendto(s,finalPktToSent,inPktSize+14,0,(struct sockaddr *) &si_other, slen);
		printf("----SEND PACKET %s\n",parm4SeqNum);
		fileLen = fileLen -(bytesSent-14);// reduce actual filesize once data is recieved
		if(fileLen <=inPktSize)// for Last Packet or if file size is less than packet size then only one packet will be sent
			{
				inPktSize=fileLen;
				sprintf(parm3PktSize,"%ld",fileLen);
				sprintf(parm2IsLastPkt,"%s","|Y");
			}
		if(seqNumber==totalAck){break;}
		}
		//Receiving the Ack from server.
		for(int j=0;j<windowSize;j++)
		{
			int result = recvfrom(s, bufferAck, 4, 0,(struct sockaddr *) &si_other, &slen); 
			if(result<0){perror("Ack not sent by server-"); exit(1);}
			else {
			printf("----RECEIVE ACK %s\n",bufferAck);
			
			int ackRecived = atoi(bufferAck);
			if(ackRecived==totalAck-1)
			{
				printf("----CLOSED CONNECTION\n");
				exit(0);			
			}
			
		}

		}
}
return(0);

}