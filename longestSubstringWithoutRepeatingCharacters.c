#include <stdio.h>

int lengthOfLongestSubstring(char* s) {
    int n = strlen(s), maxLen = 0, start = 0;
    int lastIndex[128] = {-1};

    for (int i = 0; i < 128; i++) lastIndex[i] = -1;

    for (int i = 0; i < n; i++) {
        if (lastIndex[s[i]] >= start) {
            start = lastIndex[s[i]] + 1;
        }
        lastIndex[s[i]] = i;
        int currLen = i - start + 1;
        if (currLen > maxLen) {
            maxLen = currLen;
        }
    }
    return maxLen;
}

int main(){
    char *s[5*10001];
    scanf("%5000s", &s);
    
    int ans = lengthOfLongestSubstring(s);
    printf("%d", ans);
    return 0;
}
