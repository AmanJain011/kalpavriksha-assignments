#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(){

    char inputStr[100] = {'\0'};
    scanf("%[^\n]", inputStr);

    int length = strlen(inputStr);

    if(length == 0){
        return 0;
    }
    
    int *freq = (int *)malloc(sizeof(int)*26);
    for(int i=0; i<26; i++){
        freq[i] = 0;
    }

    char flagChar = '\0';

    for(int i=0; i<length; i++){
        if(freq[inputStr[i] - 'a'] == 0){
            if(flagChar != '\0'){
                printf("%c", flagChar);
                continue;
            }
            
            printf("%c", inputStr[i]);
            freq[inputStr[i] - 'a'] = 1;

            flagChar = inputStr[i];
        }else{
            if(flagChar == inputStr[i]){
                flagChar = '\0';
            }
            printf("-1");
        }
    }

    return 0;
}
