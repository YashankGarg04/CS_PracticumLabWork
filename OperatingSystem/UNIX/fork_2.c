/*
Write a C program where the parent process initializes an integer variable x = 100. Next, call fork() to create a child process
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int x = 100;
    printf("Initial Value %d (PID: %d)\n", x, (int)getpid());
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "Fork Failed\n");
    } else if(rc == 0){
        x=200;
        printf("Child Value %d(PID : %d)\n", x, (int)getpid());
    }else {
        x=300;
        printf("Parent of %d has Value %d (PID:%d)\n", rc, x, (int)getpid());
    }
    return 0;
}