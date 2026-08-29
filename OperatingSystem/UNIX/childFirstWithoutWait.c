/*
Enforcing Process Ordering Without wait()

Write a C program using fork() such that:

The child process prints "hello\n".

The parent process prints "goodbye\n".

You must guarantee that the child process always prints first, but you are not allowed to call wait() or waitpid() in the parent process.

Explore and discuss different synchronization mechanisms in Unix/Linux to achieve this deterministic ordering.
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(){
    int fd[2];
    if(pipe(fd)<0){
        perror("pipe failed\n");
        exit(1);
    }
    pid_t pid = fork();
    if (pid<0){
        perror("Fork Failed");
        exit(1);
    } else if (pid==0){
        close(fd[0]);
        printf("Hello\n");
        char signal = 'X';
        write(fd[1], &signal, 1);
        close(fd[1]);
        exit(0);
    } else {
        close(fd[1]);
        char buf;
        read(fd[0], &buf, 1);
        printf("GoodBye\n");
        close(fd[0]);
        exit(0);
    }
    return 0;
}