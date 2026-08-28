/*
Write a function void decToBinary(int n) that converts a decimal number to its binary representation
*/

#include <stdio.h>
#include <math.h>
#include <string.h>

int power(int n){
    int flag=0;
    int i = 0;
    while (flag == 0){
        int m = pow(2,i);
        if(m>n){
            flag = 1;
            break;
        }
        i++;
    }
    int j = i-1;
    return j;
}
void decToBinary(int n){
    if(n<0){
        printf("Invalid Number");
    }
    else if(n==0){
        printf("0");
    }
    else{
        int a = power(n);
        int arr[100]= {0};
        int j = 0;
        for(int i=a; i>=0;i--){
            int p = pow(2, i);
            if(n>=p){
                arr[j] = 1;
                n -= p;
            }
            else{
                arr[j] = 0;
            }
            j++;
        }
        for(int i=0;i<=a;i++){
            printf("%d", arr[i]);
        }
    }
}
int main(){
    int n = 0;
    decToBinary(n);
    return 0;
}