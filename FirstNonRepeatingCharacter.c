#include <stdio.h>
#include <string.h>

int main()
{
    char inputString[100];
    char character;
    
    scanf("%[^\n]", inputString);
    getchar();
    scanf("%c", &character);
    
    int frequency[51] = {0};
    int length = strlen(inputString);
    
    for(int i=0; i<length; i++){
        if(inputString[i] == ' '){
            continue;
        }
        if(inputString[i] >= 'a' && inputString[i] <= 'z'){
            frequency[inputString[i] - 'a']++;
        }
        if(inputString[i] >= 'A' && inputString[i] <= 'Z'){
            frequency[inputString[i]-'A' + 26]++;
        }
        
    }
    
    for(int i=0; i<length; i++){
        if(inputString[i] == ' '){
            continue;
        }
        
        if(inputString[i] >= 'a' && inputString[i] <= 'z'){
            if(frequency[inputString[i]-'a'] == 1){
                inputString[i] = character;
                break;
            }
        }
        if(inputString[i] >= 'A' && inputString[i] <= 'Z'){
            if(frequency[inputString[i]-'A' + 26] == 1){
                inputString[i] = character;
                break;
            }
        }
        
    }
    
    printf("%s", inputString);

    return 0;
}
