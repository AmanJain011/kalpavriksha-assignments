#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROW_LENGTH 100
#define MAX_COLUMN_LENGTH 100
#define MAX_STRING_LENGTH 51

typedef struct s
{
    char data[MAX_STRING_LENGTH];
} String;

int isFrequencyChange(char str[], String array[], int frequency[], int length){
    for(int i=0; i<length; i++){
        if(!strcmp(str, array[i].data)){
            frequency[i]++;
            return 1;
        }
    }
    return 0;
}

int main(){
    int rowCount;
    int columnCount;

    scanf("%d", &rowCount);
    scanf("%d", &columnCount);

    String matrix[MAX_ROW_LENGTH][MAX_COLUMN_LENGTH];

    for(int row=0; row<rowCount; row++){
        for(int column=0; column<columnCount; column++){
            scanf("%50s", matrix[row][column].data);
        }
    }

    String array[MAX_ROW_LENGTH*MAX_COLUMN_LENGTH];
    int frequency[MAX_ROW_LENGTH*MAX_COLUMN_LENGTH] = {0};

    int position = 0;
    for(int row=0; row<rowCount; row++){
        for(int column=0; column<columnCount; column++){
            if(!isFrequencyChange(matrix[row][column].data, array, frequency, position)){
                strcpy(array[position].data, matrix[row][column].data);
                frequency[position]++;
                position++;
            }
        }
    }

    printf("<<----------------------------------------------->>\n");
    
    for(int i=0; i<position; i++){
        if(frequency[i] >= 2){
            printf("%s - %d\n", array[i].data, frequency[i]);
        }
    }
    
    return 0;
}