#include <stdio.h>
#include <stdlib.h>

int stringLength(char *str){
    int count = 0;
    while(str[count++] != '\0');
    return count-1;
}

char *intToStr(int number){
    char *numberStr = (char*)malloc(sizeof(char)*5);
    sprintf(numberStr, "%d", number);
    return numberStr;
}

int compress(char* chars, int charsSize) {
    int idx=0;
    char current = chars[0];
    int count = 0;
    for(int i=0; i<charsSize; i++){
        if(chars[i] != current){
            chars[idx++] = current;
            if(count != 1){
                char *numberStr = intToStr(count);
                int len = stringLength(numberStr);
                for(int j=0; j<len; j++){
                    chars[idx++] = numberStr[j];
                }
                free(numberStr);
            }
            count = 1;
            current = chars[i];
        }else{
            count++;
        }
    }

    chars[idx++] = current;
    if(count > 1){
        char *numberStr = intToStr(count);
        int len = stringLength(numberStr);
        for(int j=0; j<len; j++){
            chars[idx++] = numberStr[j];
        }
        free(numberStr);
    }

    return idx;
}

int main(){
    char str[4004];
    int count = 0;
    
    char ch;
    scanf("%c", &ch);
    while(scanf("%c",&str[count])){
        scanf("%c", &ch);
        count++;
        if(ch == ']'){
            break;
        }
    }
    
    int len = compress(str, count);
    
    printf("[");
    for(int i=0; i<len; i++){
        printf("%c", str[i]);
        if(i != len-1){
            printf(",");
        }
    }
    printf("]");
    
    return 0;
}
