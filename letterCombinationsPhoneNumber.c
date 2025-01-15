#include <stdio.h>
#include <stdlib.h>

void backtrack(char* digits, int index, char* current, char** result, int* returnSize, char* map[]) {
    if (index == strlen(digits)) {
        result[*returnSize] = (char*)malloc(sizeof(char) * (strlen(current) + 1));
        strcpy(result[*returnSize], current);
        (*returnSize)++;
        return;
    }

    int digit = digits[index] - '0';
    for (int i = 0; map[digit][i] != '\0'; i++) {
        current[index] = map[digit][i];
        backtrack(digits, index + 1, current, result, returnSize, map);
    }
}

char** letterCombinations(char* digits, int* returnSize) {
    if (digits == NULL || strlen(digits) == 0) {
        *returnSize = 0;
        return NULL;
    }

    char* map[] = {
        "", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"
    };

    int maxCombinations = 1;
    for (int i = 0; i < strlen(digits); i++) {
        int digit = digits[i] - '0';
        maxCombinations *= strlen(map[digit]);
    }

    char** result = (char**)malloc(sizeof(char*) * maxCombinations);
    *returnSize = 0;

    char* current = (char*)malloc(sizeof(char) * (strlen(digits) + 1));
    current[strlen(digits)] = '\0';

    backtrack(digits, 0, current, result, returnSize, map);

    free(current);
    return result;
}


int main(){
    char digits[6];
    scanf("%5s", &digits);
    int returnSize;
    char **answers = letterCombinations(digits, &returnSize);
    
    printf("[");
    for(int i=0; i<returnSize; i++){
        printf("%s", answers[i]);
        if(i!=returnSize-1){
            printf(",");
        }
    }
    printf("]");
    
    return 0;
}
