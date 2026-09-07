/* pthread_hello.c - hello with several pthreads
 *
 * By: Blaise Barney, Lawrence Livermore National Laboratory
 * Modified: T.A. Gonsalves, IIT Mandi
 * Date: 28 Feb 2023
 * Modified: Sreelakshmi Manjunath, IIT Mandi
 * Date: 4 April 2024
 */

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUM_THREADS     5

void *PrintHello(void *threadid) /* Each thread runs this function */
{
   long tid;
   tid = (long)threadid;
   printf("Hello World! It's me, thread #%ld!\n", tid);
   /* sleep() for concurrency, thread completion order reverse of start order */
   sleep(NUM_THREADS - tid);
   printf("thread #%ld exiting\n", tid);
   pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
   pthread_t threads[NUM_THREADS]; /* IDs of the created threads */
   int rc;
   long t;
   
   for(t=0; t<NUM_THREADS; t++)
     {
      printf("In main: creating thread %ld\n", t);
      rc = pthread_create(&threads[t], NULL, PrintHello, (void *)t);
      if (rc){
         printf("ERROR; return code from pthread_create() is %d\n", rc);
         exit(-1);
      }
   }

   /* main() waits for all threads to exit */
   pthread_exit(NULL);
}
