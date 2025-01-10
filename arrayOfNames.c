#include <stdio.h>

#define MAX_NAME_LENGTH 50
#define MAX_ROWS 10
#define MAX_COLUMNS 101

int startsWithVowel(char name[MAX_NAME_LENGTH + 1]){
    char firstChar = name[0];
    return (firstChar == 'A' || firstChar == 'E' || firstChar == 'I' || firstChar == 'O' || firstChar == 'U' || firstChar == 'a' || firstChar == 'e' || firstChar == 'i' || firstChar == 'o' || firstChar == 'u');
}

void clearBuffer(){
    while (getchar() != '\n');
}

int getIntegerInput(char *prompt, int minValue, int maxValue){
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1 || value < minValue || value > maxValue){
        printf("Invalid Input.\n");
        printf("%s", prompt);
        clearBuffer();
    }
    clearBuffer();
    return value;
}

int stringLength(char *string){
    int count = 0;
    while(string[count++] != '\0');
    return count;
}

void stringCopy(char *destination, char *source){
    int count = 0;
    while (source[count] != '\0') {
        destination[count] = source[count];
        count++;
    }
    destination[count] = '\0';
}

int main(){
    int vowelCount = 0;
    char longestName[MAX_NAME_LENGTH + 1];
    int maxLength = 0;

    int rowCount = getIntegerInput("Enter number of rows: ", 1, MAX_ROWS);
    int columnCount = getIntegerInput("Enter number of rows: ", 1, MAX_COLUMNS);

    char names[MAX_ROWS][MAX_COLUMNS][MAX_NAME_LENGTH + 1];

    printf("Enter the names:\n");
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        for (int colIndex = 0; colIndex < columnCount; colIndex++)
        {
            printf("Name at (%d,%d): ", rowIndex, colIndex);
            scanf("%50s", names[rowIndex][colIndex]);
            clearBuffer();
            
            if (startsWithVowel(names[rowIndex][colIndex]))
            {
                vowelCount++;
            }

            int nameLength = stringLength(names[rowIndex][colIndex]);
            if (nameLength > maxLength)
            {
                maxLength = nameLength;
                stringCopy(longestName, names[rowIndex][colIndex]);
            }
        }
    }

    printf("\nThe 2D array of names is:\n");
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        for (int colIndex = 0; colIndex < columnCount; colIndex++)
        {
            printf("%s ", names[rowIndex][colIndex]);
        }
        printf("\n");
    }

    printf("\nNumber of names starting with a vowel: %d\n", vowelCount);
    printf("The longest name: %s\n", longestName);

    return 0;
}
