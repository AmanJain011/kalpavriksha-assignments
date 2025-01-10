#include <stdio.h>
#include <stdlib.h>

#define MAX_ROW_LENGTH 100
#define MAX_COLUMN_LENGTH 100

int getIntegerInput(char *prompt);
void clearBuffer();
int shouldContinue();
void displayMenu();

void rotate90(int matrix[][MAX_COLUMN_LENGTH], int *rowCount, int *columnCount);
void rowWiseLeftRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount);
void rowWiseRightRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount);
void columnWiseUpRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount);
void columnWiseDownRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount);

void transposeMatrix(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount);
void swapNumbers(int *value1, int *value2);
void printMatrix(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount);

int main() {
    int rowCount, columnCount;
    int matrix[MAX_ROW_LENGTH][MAX_COLUMN_LENGTH];

    rowCount = getIntegerInput("Enter number of Rows: ");
    columnCount = getIntegerInput("Enter number of Columns: ");

    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++) {
            printf("Enter element at (%d, %d): ", row + 1, column + 1);
            matrix[row][column] = getIntegerInput("");
        }
    }

    printMatrix(matrix, rowCount, columnCount);

    while (1) {
        displayMenu();
        int choice = getIntegerInput("Enter Your Choice --> ");
        if (choice < 1 || choice > 5) {
            printf("Invalid choice! Try again.\n");
            continue;
        }

        int rotationCount = getIntegerInput("Enter How Many Times to Rotate: ");
        printf("Result: \n");

        for (int i = 0; i < rotationCount; i++) {
            switch (choice) {
                case 1:
                    while(rotationCount--){
                        rotate90(matrix, &rowCount, &columnCount);
                    }
                    break;
                case 2:
                    while(rotationCount--){
                        rowWiseLeftRotation(matrix, rowCount, columnCount);
                    }
                    break;
                case 3:
                    while(rotationCount--){
                        rowWiseRightRotation(matrix, rowCount, columnCount);
                    }
                    break;
                case 4:
                    while(rotationCount--){
                        columnWiseUpRotation(matrix, rowCount, columnCount);
                    }
                    break;
                case 5:
                    while(rotationCount--){
                        columnWiseDownRotation(matrix, rowCount, columnCount);
                    }
                    break;
            }
        }

        printMatrix(matrix, rowCount, columnCount);

        if (!shouldContinue()) break;
    }

    return 0;
}

int getIntegerInput(char *prompt) {
    int value;
    printf("%s", prompt);
    while (scanf("%d", &value) != 1) {
        printf("Invalid Input. Try again.\n");
        clearBuffer();
    }
    clearBuffer();
    return value;
}

void clearBuffer() {
    while (getchar() != '\n');
}

int shouldContinue() {
    char choice;
    while (1) {
        printf("Continue? (y/n): ");
        scanf("%c", &choice);
        clearBuffer();
        if (choice == 'y' || choice == 'Y') return 1;
        if (choice == 'n' || choice == 'N') return 0;
        printf("Invalid choice. Please enter 'y' or 'n'.\n");
    }
}

void displayMenu() {
    printf("<<----------------MENU---------------->>\n");
    printf("1. Matrix-Level Rotation (90°).\n");
    printf("2. Row-Wise Rotation (Left).\n");
    printf("3. Row-Wise Rotation (Right).\n");
    printf("4. Column-Wise Rotation (Up).\n");
    printf("5. Column-Wise Rotation (Down).\n");
}

void rotate90(int matrix[][MAX_COLUMN_LENGTH], int *rowCount, int *columnCount) {
    int temp[MAX_ROW_LENGTH][MAX_COLUMN_LENGTH];
    int newRowCount = *columnCount;
    int newColumnCount = *rowCount;

    for (int row = 0; row < *rowCount; row++) {
        for (int column = 0; column < *columnCount; column++) {
            temp[column][*rowCount - 1 - row] = matrix[row][column];
        }
    }

    *rowCount = newRowCount;
    *columnCount = newColumnCount;

    for (int row = 0; row < *rowCount; row++) {
        for (int column = 0; column < *columnCount; column++) {
            matrix[row][column] = temp[row][column];
        }
    }
}

void rowWiseLeftRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount) {
    for (int row = 0; row < rowCount; row++) {
        int temp = matrix[row][0];
        for (int col = 0; col < columnCount - 1; col++) {
            matrix[row][col] = matrix[row][col + 1];
        }
        matrix[row][columnCount - 1] = temp;
    }
}

void rowWiseRightRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount) {
    for (int row = 0; row < rowCount; row++) {
        int temp = matrix[row][columnCount - 1];
        for (int col = columnCount - 1; col > 0; col--) {
            matrix[row][col] = matrix[row][col - 1];
        }
        matrix[row][0] = temp;
    }
}

void columnWiseUpRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount) {
    for (int column = 0; column < columnCount; column++) {
        int temp = matrix[0][column];
        for (int row = 0; row < rowCount - 1; row++) {
            matrix[row][column] = matrix[row + 1][column];
        }
        matrix[rowCount - 1][column] = temp;
    }
}

void columnWiseDownRotation(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount) {
    for (int column = 0; column < columnCount; column++) {
        int temp = matrix[rowCount - 1][column];
        for (int row = rowCount - 1; row > 0; row--) {
            matrix[row][column] = matrix[row - 1][column];
        }
        matrix[0][column] = temp;
    }
}

void printMatrix(int matrix[][MAX_COLUMN_LENGTH], int rowCount, int columnCount) {
    for (int row = 0; row < rowCount; row++) {
        for (int column = 0; column < columnCount; column++) {
            printf("%d ", matrix[row][column]);
        }
        printf("\n");
    }
}
