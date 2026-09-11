#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <string.h>

#define MAXLEN 100
#define PORT 12351

int main(int argc, char **argv)
{
	int s;
	char buff[MAXLEN], ACK[3];
	struct sockaddr_in saddr;
	FILE *fp;

	if(argc!=3)
	{
		printf("Usage:%s <Server’s address> <file name>\n",argv[0]);
		exit(0);
	}
	/* create socket "s"*/
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s<0)
	{
		perror("socket");
		exit(1);
 	}
	saddr.sin_family=AF_INET;

	/*  supply port number in a format that the network can read */
	saddr.sin_port= htons(PORT);

	if(inet_pton(AF_INET,argv[1],&saddr.sin_addr)<=0)
	{
		printf("Error. Invalid IP address\n");
		exit(1);
	}
	/* connect socket, if doesn't connect print error */	
	if(connect(s,(struct sockaddr *) &saddr, sizeof(saddr))<0){
		perror("ERROR in connecting\n");
		exit(1);
	}

	write(s,argv[2],strlen(argv[2]));
	if((fp=fopen(argv[2],"r"))==NULL)
	{
		perror(argv[2]);
		exit(1);
	}

	/* read acknowledgements */
	read(s,ACK,2);
	while(1)
	{
		fgets(buff,MAXLEN-1,fp);
		if(feof(fp))
			break;
		/* write contents of buff to the socket */
		write(s, buff, strlen(buff));
		/* read acknowledgement */
		read(s, ACK, 2);
	}
	/* close file handle */
	fclose(fp);
    close(s);
	/* close socket*/
}
