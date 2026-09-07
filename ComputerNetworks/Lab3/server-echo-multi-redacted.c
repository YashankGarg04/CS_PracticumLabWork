/* A simple server in the internet domain using TCP
 *   The port number is passed as an argument
 * Complete lines marked with ?????
 *
 */

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

#define MAX_INPUT_SIZE 256
#define COMPUTE_DELAY  10	/* Delay before response to client */

void error(char *msg)
{
    perror(msg);
    exit(1);
}

void *PrintHello(int newsockfd) /* Each thread runs this function */
  {
    char msg[256];		// Temp string buffer        
    char buffer[256];	// I/O buffer
    int n;
    
    /* read message from client */

    bzero(buffer, MAX_INPUT_SIZE);
    n = read(newsockfd, buffer, MAX_INPUT_SIZE - 1);
    if (n < 0) error("ERROR reading from socket");

    printf("Here is the message: %s\n", buffer);

    sleep(COMPUTE_DELAY);	/* Simulate computation */

    /* send reply  to client */
    printf("Sending reply %s\n", buffer);

    strcpy(msg, "I got your message");
    n = write(newsockfd, msg, strlen(msg));
    if (n < 0) 
      error("ERROR writing to socket");

    printf("thread #%ld exiting\n", pthread_self());
    pthread_exit(NULL);

  } /* End PrintHello */

int main(int argc, char *argv[])
{
     int sockfd, newsockfd, portno, clilen;
     char buffer[MAX_INPUT_SIZE];
     struct sockaddr_in serv_addr, cli_addr;
     int n;
     pthread_t thread_id; /* IDs of the created threads */
     int rc;
     long t;
     
     if (argc < 2)
       error("ERROR, no port provided");

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
    
     while(1)
       {
	 /* listen for incoming connection requests */

	 listen(sockfd, 5);
	 clilen = sizeof(cli_addr);

	 /* accept a new request, create a newsockfd */

	 newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
	 if (newsockfd < 0) 
	   error("ERROR on accept");

	 rc = pthread_create(&thread_id, NULL, PrintHello, (void *)(intptr_t)newsockfd);

	 if (rc){
	   printf("ERROR; return code from pthread_create() is %d\n", rc);
	   exit(-1);
	 }
       } /* end while(1) */

   /* main() waits for all threads to exit */
   pthread_exit(NULL);

}
