#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_NAME_LENGTH 50
#define MAX_ROWS 10
#define MAX_COLUMNS 101

int startsWithVowel(char name[MAX_NAME_LENGTH + 1])
{
    char firstChar = tolower(name[0]);
    return (firstChar == 'a' || firstChar == 'e' || firstChar == 'i' || firstChar == 'o' || firstChar == 'u');
}

int main()
{
    int rowCount, colCount;
    int vowelCount = 0;
    char longestName[MAX_NAME_LENGTH + 1];
    int maxLength = 0;

    printf("Enter number of rows: ");
    if(scanf("%d", &rowCount) != 1){
      return 1;
    }
    printf("Enter number of columns: ");
    if(scanf("%d", &colCount) != 1){
      return 1;
    }

    if (rowCount < 1 || rowCount > MAX_ROWS || colCount < 1 || colCount > MAX_COLUMNS)
    {
        printf("Invalid input for rows or columns.\n");
        return 1;
    }

    char names[MAX_ROWS][MAX_COLUMNS][MAX_NAME_LENGTH + 1];

    printf("Enter the names:\n");
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        for (int colIndex = 0; colIndex < colCount; colIndex++)
        {
            printf("Name at (%d,%d): ", rowIndex, colIndex);
            scanf("%s", names[rowIndex][colIndex]);

            if (startsWithVowel(names[rowIndex][colIndex]))
            {
                vowelCount++;
            }

            int nameLength = strlen(names[rowIndex][colIndex]);
            if (nameLength > maxLength)
            {
                maxLength = nameLength;
                strcpy(longestName, names[rowIndex][colIndex]);
            }
        }
    }

    printf("\nThe 2D array of names is:\n");
    for (int rowIndex = 0; rowIndex < rowCount; rowIndex++)
    {
        for (int colIndex = 0; colIndex < colCount; colIndex++)
        {
            printf("%s ", names[rowIndex][colIndex]);
        }
        printf("\n");
    }

    printf("\nNumber of names starting with a vowel: %d\n", vowelCount);
    printf("The longest name: %s\n", longestName);

    return 0;
}
