/*
Write a C function
int countSpaces(char *str)
that counts the number of spaces in a string
Remember to include <string.h> and ' ' is the space character.
For example:
Test                                                Result
printf("%d\n", countSpaces("hello world"));         1
printf("%d\n", countSpaces("hello world again"));   2
*/
#include <stdio.h>
#include <string.h>

int countSpaces(char *str){
    int n = strlen(str);
    int m = 0;
    for(int i=0;i<n;i++){
        if (str[i]==' '){
            m++;
        }
    }
    return m;
}
int main(){
    printf("%d\n", countSpaces("hello world"));
    printf("%d\n", countSpaces("hello world again"));
    return 0;
}