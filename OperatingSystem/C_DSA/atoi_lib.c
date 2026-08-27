/*Write a c function nextPow() which accepts a positive integer x as string and determines the smallest power of 2 greater than x. It then returns that exponent.

For eg, if the input is "300", the output should be 9, because 2^9 > 300.

Use the atoi library function to convert a string into integer.

Function prototype:

int nextPow(char *str);*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int nextPow(char *str){
    int n = atoi(str);
    int flag = 0;
    int i =0;
    while(flag==0){
        int m = pow(2,i);
        if(m > n){
            flag = 1;
            break;
        }
        else{
            i++;
        }
    }
    return i;
}

int main(){
    printf("%d",nextPow("100"));
    return 0;
}