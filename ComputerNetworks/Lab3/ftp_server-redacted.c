#include<stdio.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <string.h>


#define MAXLEN 100
#define PORT 12351

void error(char *msg){
	perror(msg);
	exit(1);
}

int main(int argc,char **argv)
{
	int s, connfd, len, n, portno;
	char recv[MAXLEN], recvaddr[16];
	struct sockaddr_in saddr, caddr;
	FILE *fp;

	/* Create socket "s" */
	s = socket(AF_INET, SOCK_STREAM, 0);
	if(s<0) error("ERROR socket not created");

	saddr.sin_family=AF_INET;
	/* assign IP address */
	saddr.sin_addr.s_addr= INADDR_ANY;
	/* assign port number */
	saddr.sin_port= htons(PORT);

	if(bind(s,(struct sockaddr *) &saddr,sizeof(saddr))<0)
	{
		error("ERROR in binding");
	}
	/* listen on the created socket, upto 10 clients in wait in the queue while the server is busy */
	listen(s, 5);
	len = sizeof(caddr);

	while(1)
	{
		printf("Waiting for request...\n");
		len=sizeof(struct sockaddr_in);
		/* accept client's request on socket "connfd"*/
		connfd = accept(s, (struct sockaddr *) &caddr, &len);
		if (connfd <0)
			error("ERROR on accept");

		/* read from the socket associated with the client*/
		bzero(recv, MAXLEN);
		n = read(connfd, recv, MAXLEN-1);
		if (n<0) error("ERROR cannot read from socket");
		recv[n]='\0';
		fp=fopen(recv,"w");
		/* send message "OK" to client */
		write(connfd, "OK", 2);

		while((n=read(connfd,recv,MAXLEN-1))>0)
		{
			recv[n]='\0';
			fwrite(recv,1,strlen(recv),fp);
			write(connfd,"OK",2);
		}
		/* close the file handle used */
		fclose(fp);
		inet_ntop(AF_INET,&caddr.sin_addr,recvaddr,sizeof(recvaddr));
 		printf("File uploaded from %s",recvaddr);
		/* close the socket */
		close(connfd);
	}
}
