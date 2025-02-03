#include <stdio.h>
#include <string.h>

int main(){
    char str1[201];
    char str2[201];

    scanf("%s", str1);
    scanf("%s", str2);

    int len1 = strlen(str1);
    int len2 = strlen(str2);

    char modefiedStr1[201] = {'\0'};
    char modefiedStr2[201] = {'\0'};

    int j1=0;
    for(int i=0; i<len1; i++){
        if(str1[i] != '#'){
            modefiedStr1[j1] = str1[i];
            j1++;
        }else{
            j1--;
        }
    }

    int j2=0;
    for(int i=0; i<len2; i++){
        if(str2[i] != '#'){
            modefiedStr2[j2] = str2[i];
            j2++;
        }else{
            j2--;
        }
    }

    if(!strcmp(modefiedStr1, modefiedStr2)){
        printf("True\n");
    }else{
        printf("Fasle\n");
    }

    return 0;
}
