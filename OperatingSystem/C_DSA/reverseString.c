/*
Write void reverseString(char *str) that reverses a string in-place without creating a second array.
*/

#include <stdio.h>
#include <string.h>

void reverseString(char *str){
    int left = 0;
    int right = strlen(str)-1;
    while (left<right){
        char temp = str[left];
        str[left] = str[right];
        str[right] = temp;
        left++;
        right--;
    }
}
int main(){
    char str[] = "Hello, I am Yashank Garg";
    reverseString(str);
    printf("%s\n", str);
    return 0;
}
