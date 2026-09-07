#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <string.h>


#define MAXLEN 100
#define PORT 12345

int main(int argc,char **argv)
{
	int s, connfd, len, n, portno;
	char recv[MAXLEN], recvaddr[16];
	struct sockaddr_in saddr, caddr;
	FILE *fp;

	/* Create socket "s" */
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s<0)
	{
		perror("socket");
		exit(0);
	}
	saddr.sin_family=AF_INET;
	/* assign IP address */
	saddr.sin_addr.s_addr= INADDR_ANY;
	/* assign port number */
	portno = atoi(argv[1]);
	saddr.sin_port= htons(portno);

	if(bind(s,(struct sockaddr *)&saddr,sizeof(saddr))<0)
	{
		perror("bind");
		exit(0);
	}
	/* listen on the created socket, upto 10 clients in wait in the queue while the server is busy */
	listen(sockfd, 5);
	len = sizeof(caddr);

	while(1)
	{
		printf("Waiting for request...\n");
		len=sizeof(struct sockaddr_in);
		/* accept client's request on socket "connfd"*/
		connfd = accept(s, (struct saddr *) &caddr, &len);
		if (connfd <0)
			error("ERROR on accept");

		/* read from the socket associated with the client*/
		???????????

		recv[n]='\0';
		fp=fopen(recv,"w");
		/* send message "OK" to client */
		??????????????????
		while((n=read(connfd,recv,MAXLEN-1))>0)
		{
			recv[n]='\0';
			fwrite(recv,1,strlen(recv),fp);
			write(connfd,"OK",2);
		}
		/* close the file handle used */
		????????????
		inet_ntop(AF_INET,&caddr.sin_addr,recvaddr,sizeof(recvaddr));
 		printf("File uploaded from %s",recvaddr);
		/* close the socket */
		????????????
	}
}
