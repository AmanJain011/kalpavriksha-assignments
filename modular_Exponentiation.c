#include <stdio.h>

void clearBuffer();
int getIntegerInput(const char *prompt, int min);
int compute(int base, int exponent, int mod);

int main(){
    int base, exponent, mod, result;

    printf("<<----------------------------------------->>\n");

    while (1) {
        base = getIntegerInput("Base (B): ", 0);
        exponent = getIntegerInput("Exponent (E): ", 0);
        mod = getIntegerInput("Modulus (M): ", 2);
        result = compute(base, exponent, mod);
        printf("Result: %d\n", result);
        printf("<<----------------------------------------->>\n");
    }
    
    return 0;
}

void clearBuffer(){
    while (getchar() != '\n');
}

int getIntegerInput(const char *prompt, int min) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || value < min) {
        printf("Invalid number.\n");
        printf("Please enter a valid %s", prompt);
        clearBuffer();
    }
    clearBuffer();
    return value;
}

int compute(int base, int exponent, int mod){
    base %= mod;
    int result = 1;

    while (exponent > 0){
        if(exponent & 1){
            result = (int)((1LL * result * base) % mod);;
        }

        base = (int)((1LL * base * base) % mod);;
        exponent >>= 1;
    }
    
    return result;
}
