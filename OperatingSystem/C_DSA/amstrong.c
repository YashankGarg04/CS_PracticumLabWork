/*
Write int isArmstrong(int n) that sums each digit raised to the power of the
total number of digits using pow() and determines if it equals n
*/
#include <stdio.h>
#include <math.h>

int isArmstrong(int n){
    if(n<0){
        return 2;
    }
    int digCount;
    if(n==0){
        digCount = 0;
    }
    if(n>0){
        digCount = log10(n)+1;
    }
    int sum=0;
    int a = n;
    while(a>0){
        int b = a%10;
        int c = (int)(pow(b,digCount)+0.5);
        sum += c;
        a = a/10;
    }
    if(sum==n){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    int n = 153;
    int r = isArmstrong(n);
    if(r == 0){
        printf("Not Armstrong");
    }
    else if(r == 1){
        printf("Is an Armstrong");
    }
    else{
        printf("Please enter a Valid Number");
    }
}