#include <stdio.h>
#include <stdlib.h>

int diagonalSum(int** mat, int matSize, int* matColSize) {
    int sum = 0; 
    for(int i=0; i<matSize; i++){
        sum += mat[i][i];
        if(i != *matColSize-i-1){
            sum += mat[i][*matColSize-i-1];
        }
    }

    return sum;
}

int main(){
    int rowLength;
    int columnLength;
    
    scanf("%d", &rowLength);
    scanf("%d", &columnLength);
    
    int **matrix = (int **)malloc(sizeof(int *)*rowLength);
    for(int i=0; i<rowLength; i++){
        matrix[i] = (int *)malloc(sizeof(int)*columnLength);
    }
    
    for(int i=0; i<rowLength; i++){
        for(int j=0; j<columnLength; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    printf("%d", diagonalSum(matrix, rowLength, &columnLength));
    return 0;
}
