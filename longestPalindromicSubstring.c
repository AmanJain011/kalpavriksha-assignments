#include <stdio.h>
#include <stdlib.h>

char* longestPalindrome(char* s);
void stringCopy(char *src, char **dest, int i, int j);
int stringLength(char *s);
int isPalindrome(char *s, int i, int j);

int main(){
    char string[1001];
    scanf("%1000s", string);
    printf("%s", longestPalindrome(string));
    return 0;
}


int isPalindrome(char *s, int i, int j){
    while(i<j){
        if(s[i] != s[j]){
            return 0;
        }
        i++;
        j--;
    }
    return 1;
}

int stringLength(char *s){
    int count = 0;
    while(s[count++] != '\0');
    return count-1;
}

void stringCopy(char *src, char **dest, int i, int j){
    *dest = (char *)realloc(*dest, sizeof(char)*(j-i+2));
    int k=0;
    for(; i<=j; i++){
        (*dest)[k++] = src[i];
    }

    (*dest)[k] = '\0';
}

char* longestPalindrome(char* s) {
    int maxLength = 0;
    char *ans = NULL;

    int length = stringLength(s);
    for(int i=0; i<length; i++){
        for(int j=0; j<length; j++){
            if(isPalindrome(s, i, j)){
                if(maxLength < (j-i+1)){
                    maxLength = j-i+1;
                    stringCopy(s, &ans, i, j);
                }
            }
        }
    }

    return ans;
}
