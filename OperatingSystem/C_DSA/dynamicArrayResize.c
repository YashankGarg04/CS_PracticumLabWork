/*
Write a program that uses malloc() to allocate memory for N integers,
fills them, and then uses realloc() to double the size of the array dynamically
*/
#include <stdio.h>
#include <stdlib.h>

int main(){
    int arrSize;
    printf("Size of the array you want: ");
    scanf("%d", &arrSize);
    int *arr = (int *)malloc(arrSize*sizeof(int));
    if(arr = NULL){
        printf("\nArray not Created");
        free(arr);
    }
    else{
        printf("\nArray Created");
    }
    int doubleSize = 2*arrSize;
    int *temp = (int *)realloc(arr,doubleSize*sizeof(int));
    if(temp = NULL){
        printf("\nArray not Created");
        free(temp);
    }
    else{
        printf("\nArray Doubled");
    }
    return 0;
}