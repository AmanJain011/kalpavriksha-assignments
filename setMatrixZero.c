#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void setZeroes(int** matrix, int matrixSize, int* matrixColSize);

int main()
{
    int rowSize;
    int colSize;
    
    scanf("%d", &rowSize);
    scanf("%d", &colSize);
    
    int** matrix = (int **)malloc(sizeof(int *)*rowSize);
    for(int i=0; i<rowSize; i++){
        matrix[i] = (int *)malloc(sizeof(int)*colSize);
    }
    
    for(int i=0; i<rowSize; i++){
        for(int j=0; j<colSize; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    setZeroes(matrix, rowSize, &colSize);
    
    printf("[");
    for(int i=0; i<rowSize; i++){
        printf("[");
        for(int j=0; j<colSize; j++){
            printf("%d", matrix[i][j]);
            if(j != colSize-1){
                printf(" ");
            }
        }
        printf("]");
        if(i != rowSize-1){
            printf(",");
        }
    }
    printf("]");
    
    return 0;
}


void setZeroes(int** matrix, int matrixSize, int* matrixColSize) {
    bool firstRowZero = false;
    bool firstColZero = false;

    for(int row=0; row<matrixSize; row++){
        if(matrix[row][0] == 0){
            firstColZero = true;
            break;
        }
    }

    for(int col=0; col<*matrixColSize; col++){
        if(matrix[0][col] == 0){
            firstRowZero = true;
            break;
        }
    }

    for(int i=1; i<matrixSize; i++){
        for(int j=1; j<*matrixColSize; j++){
            if(matrix[i][j] == 0){
                matrix[i][0] = 0;
                matrix[0][j] = 0;
            }
        }
    }

    for(int i=1; i<matrixSize; i++){
        for(int j=1; j<*matrixColSize; j++){
            if(matrix[i][0] == 0 || matrix[0][j] == 0){
                matrix[i][j] = 0;
            }
        }
    }

    for(int i=0; i<*matrixColSize; i++){
        if(firstRowZero){
            matrix[0][i] = 0;
        }
    }

    for(int i=0; i<matrixSize; i++){
        if(firstColZero){
            matrix[i][0] = 0;
        }
    }
}
