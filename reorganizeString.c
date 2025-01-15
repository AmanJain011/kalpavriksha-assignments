#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char ch;
    int freq;
} CharFreq;

int compare(const void* a, const void* b) {
    return ((CharFreq*)b)->freq - ((CharFreq*)a)->freq;
}

char* reorganizeString(char* s) {
    int n = strlen(s), freq[26] = {0};
    for (int i = 0; i < n; i++) freq[s[i] - 'a']++;
    CharFreq chars[26];
    int count = 0;
    for (int i = 0; i < 26; i++) 
        if (freq[i]) chars[count++] = (CharFreq){'a' + i, freq[i]};
    qsort(chars, count, sizeof(CharFreq), compare);
    if (chars[0].freq > (n + 1) / 2) return "";

    char* result = malloc(n + 1);
    result[n] = '\0';
    int index = 0;
    for (int i = 0; i < count; i++) 
        while (chars[i].freq--) {
            result[index] = chars[i].ch;
            index += 2;
            if (index >= n) index = 1;
        }
    return result;
}


int main(){
    char s[501];
    scanf("%500s", s);
    
    printf("%s", reorganizeString(s));
    return 0;
}
