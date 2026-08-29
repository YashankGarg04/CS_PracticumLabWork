/*
Shared File Descriptors and Concurrent Writes Across fork()

Write a C program where the main process opens a file (e.g., output.txt) using the open() system call before calling fork()
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc, char *argv[]){
    int fd = open("output.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "fork failed\n");
    } else if(rc==0){
        const char *cm = "This is Child";
        write(fd, cm, strlen(cm));
        close(fd);
        exit(0);
    } else {
        const char *pm = "This is Parent";
        write(fd, pm, strlen(pm));
        close(fd);
    }
    return 0;
}