/*
Write int isPalindrome(char *str) returning 1 if the string reads the same forwards and backwards, and 0 otherwise
*/
#include <stdio.h>
#include <string.h>

int isPalindrome(char *str){
    int left = 0;
    int right = strlen(str)-1;
    int flag = 0;
    while((left<right) && flag == 0 ){
        if(str[left]==str[right]){
            left++;
            right--;
        }
        else{
            flag=1;
        }
    }
    if(flag ==0){
        return 1;
    }
    else{return 0;
    }
}
int main(){
    char str[] = "naman";
    int c = isPalindrome(str);
    if (c==1){
        printf("%d\nString is Palindrome", c);
    }
    else{
        printf("%d\nString is not a Palindrome", c);
    }
}