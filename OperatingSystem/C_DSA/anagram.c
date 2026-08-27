/*
Write int isAnagram(char *s1, char *s2) to check if two strings contain the exact same characters
in any order (Hint: use frequency arrays)
*/
#include <stdio.h>
#include <string.h>

int isAnagram(char *s1, char *s2){
    int f[256] = {0};
    int n1 = strlen(s1);
    int n2 = strlen(s2);
    int flag = 0;
    if (n1!=n2){
        return 0;
    }
    for(int i=0; i<n1; i++){
        unsigned char index = s1[i];
        f[index]++;
    }
    for(int i=0; i<n2;i++){
        unsigned char index = s2[i];
        f[index]--;
        if(f[index]<0){
            flag=1;
            break;
        }
    }
    if(flag==0){
        return 1;
    }
    else{
        return 0;
    }
}

int main(){
    char s1[]= "yashank";
    char s2[]= "ahhkays";
    int r = isAnagram(s1,s2);
    if(r==1){
        printf("Is Anagram");
    }
    else{
        printf("Is Not Anagram");
    }
}