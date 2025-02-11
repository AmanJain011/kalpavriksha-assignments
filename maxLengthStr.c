#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int isCharPresent(char* str1, char *str2){
    int len1 = strlen(str1);
    int len2 = strlen(str2);

    int freq[26] = {0};

    for(int i=0; i<len1; i++){
        freq[str1[i] - 'a'] = 1;
    }

    for(int i=0; i<len2; i++){
        if(freq[str2[i] - 'a'] == 1){
            return 1;
        }
    }

    return 0;
}

int main(){
    char** strings = (char **)malloc(sizeof(char *)*100);
    for(int i=0; i<100; i++){
        strings[i] = (char *)malloc(sizeof(char)*20);
    }

    int count = 0;

    getchar();
    while (scanf("%[^],]", strings[count]) == 1){
        count++;
        if(getchar() == ']') break;
    }

    int ans = 0;
    for (int i = 0; i < count; i++){
        for(int j=i+1; j<count; j++){
            if(!isCharPresent(strings[i], strings[j])){
                int len1 = strlen(strings[i]);
                int len2 = strlen(strings[j]);

                if(len2*len1 > ans){
                    ans = len2*len1;
                }
            }
        }
    }

    printf("%d", ans);
    

    return 0;
}
