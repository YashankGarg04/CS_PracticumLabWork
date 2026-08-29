/*
This is a implementation of how fork works we must use gcc comiler to run this as running directly with windows will show error which
alternatively requires WSL
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc,char *argv[]){
    printf("hello (pid:%d)\n", (int)getpid());
    int rc = fork();
    if(rc<0){
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if(rc==0){
        printf("child (pid:%d)\n", (int)getpid());
    } else{
        printf("parent of %d (pid:%d)\n", rc, (int)getpid());
    }
    return 0;
}