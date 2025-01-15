#include <stdio.h>
#include <string.h>

int isDigit(char ch) {
    return ch >= '0' && ch <= '9'; 
}

int main() {
    char ipv4[16];
    scanf("%[^\n]", ipv4);

    int length = strlen(ipv4);
    if (length > 15 || length < 7) { 
        printf("Invalid");
        return 0;
    }

    int countDecimal = 0;
    int countNumber = 0; 
    int i = 0;

    while (ipv4[i] != '\0') {
        if (isDigit(ipv4[i])) {
            int num = 0;
            int digitCount = 0;
            int startWithZero = (ipv4[i] == '0');

            while (isDigit(ipv4[i])) {
                num = num * 10 + (ipv4[i] - '0');
                digitCount++;
                i++;
            }

            if (num < 0 || num > 255 || (startWithZero && digitCount > 1)) {
                printf("Invalid");
                return 0;
            }

            countNumber++;

        } else if (ipv4[i] == '.') {
            countDecimal++;
            i++;

            if (ipv4[i] == '\0' || ipv4[i] == '.') {
                printf("Invalid");
                return 0;
            }
        } else {
            printf("Invalid");
            return 0;
        }
    }

    if (countDecimal != 3 || countNumber != 4) {
        printf("Invalid");
        return 0;
    }

    printf("Valid");
    return 0;
}
