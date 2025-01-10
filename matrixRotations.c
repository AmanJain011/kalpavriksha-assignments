#include<stdio.h>

int getIntegerInput(char *prompt);
void clearBuffer();
int **getDynamicMatrix(int row, int column);
int isShouldContinue();
void displayMenu();

void rotate90(int **matrix, int rotationCount, int rowCount, int columnCount);
void rowWiseLeftRotation(int **matrix, int rotationCount, int rowCount, int columnCount);
void rowWiseRightRotation(int **matrix, int rotationCount, int rowCount, int columnCount);
void columnWiseUpRotation(int **matrix, int rotationCount, int rowCount, int columnCount);
void columnWiseDownRotation(int **matrix, int rotationCount, int rowCount, int columnCount);

void transposeMatrix(int **matrix, int rowCount, int columnCount);

int main(){
    int rowCount;
    int columnCount;

    rowCount = getIntegerInput("Enter number of Rows: ");
    columnCount = getIntegerInput("Enter number of Columns: ");

    int **matrix = getDynamicMatrix(rowCount, columnCount);
    if(matrix == NULL){
        return 1;
    }

    for(int row = 0; row < rowCount; row++){
        int element;
        for(int column = 0; column < columnCount; column++){
            matrix[row][column] = getIntegerInput("");
        }
    }

    while (1){
        displayMenu();
        int choice = getIntegerInput("Enter Your Choice --> ");
        int rotationCount = getIntegerInput("Enter How Much Times you Want to Rotate: ");
        printf("Result: \n");

        int** (*pointerToFunction[])(int **matrix, int rotationCount, int rowCount, int columnCount) = {
            rotate90, 
            rowWiseLeftRotation, 
            rowWiseRightRotation, 
            columnWiseUpRotation, 
            columnWiseDownRotation
        };

        pointerToFunction[choice](matrix, rotationCount, rowCount, columnCount);                          

        if(!isShouldContinue()) break;
    }

    return 0;
}

int getIntegerInput(char *prompt){
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1){
        printf("Invalid Input.\n");
        clearBuffer();
    }
    clearBuffer();
    return value;
}

void clearBuffer(){
    while (getchar() != '\n');
}

int isShouldContinue(){

}

void displayMenu(){
    printf("<<----------------MENU---------------->>\n");
    printf("1. Matrix-Level Rotation (90°).\n");
    printf("2. Row-Wise Rotation (Left).\n");
    printf("3. Row-Wise Rotation (Right).\n");
    printf("4. Coumn-Wise Rotation (Up).\n");
    printf("5. Column-Wise Rotation (Down).\n");
}

int **getDynamicMatrix(int rowCount, int columnCount){
    int **matrix = (int **)malloc(sizeof(int*)*rowCount);
    if(matrix == NULL){
        printf("Dynamic Memory is not Allocated.\n");
        return NULL;
    }

    for(int row = 0; row < rowCount; row++){
        matrix[row] = (int *)malloc(sizeof(int)*columnCount);
        if(matrix[row] == NULL){
            printf("Dynamic Memory is not Allocated.\n");
            for (int i = 0; i < row; i++) {
                free(matrix[i]);
            }
            free(matrix);
            return NULL;
        }
    }
    return matrix;
}

void rotate90(int **matrix, int rotationCount, int rowCount, int columnCount){

}

void transposeMatrix(int **matrix, int rowCount, int columnCount){

}