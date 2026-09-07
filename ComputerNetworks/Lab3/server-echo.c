/* A simple server in the internet domain using TCP
   The port number is passed as an argument */
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define MAX_INPUT_SIZE 256
#define COMPUTE_DELAY  10	/* Delay before response to client */

void error(char *msg)
{
    perror(msg);
    exit(1);
}

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[MAX_INPUT_SIZE];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     if (argc < 2) {
         fprintf(stderr, "ERROR, no port provided\n");
         exit(1);
     }

     /* create socket */

     sockfd = socket(AF_INET, SOCK_STREAM, 0);
     if (sockfd < 0) 
        error("ERROR opening socket");

     /* fill in port number to listen on. IP address can be anything (INADDR_ANY) */

     bzero((char *) &serv_addr, sizeof(serv_addr));
     portno = atoi(argv[1]);
     serv_addr.sin_family = AF_INET;
     serv_addr.sin_addr.s_addr = INADDR_ANY;
     serv_addr.sin_port = htons(portno);

     /* bind socket to this port number on this machine */

     if (bind(sockfd, (struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0) 
              error("ERROR on binding");
     
     /* listen for incoming connection requests */

     listen(sockfd, 5);
     clilen = sizeof(cli_addr);

     /* accept a new request, create a newsockfd */

     newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
     if (newsockfd < 0) 
          error("ERROR on accept");

     /* read message from client */

     bzero(buffer, MAX_INPUT_SIZE);
     n = read(newsockfd, buffer, MAX_INPUT_SIZE - 1);
     if (n < 0) error("ERROR reading from socket");
     printf("Here is the message: %s\n", buffer);

     sleep(COMPUTE_DELAY);	/* Simulate computation */

     /* send reply to client */
     printf("Sending reply\n", buffer);

     n = write(newsockfd, "I got your message", 18);
     if (n < 0) error("ERROR writing to socket");
     return 0; 
}
