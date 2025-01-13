#include <stdio.h>
#include <stdlib.h>

void swapPointers(int **ptr1, int **ptr2){
    int *temp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = temp;
};

void sortMatrix(int** intervals, int intervalsSize, int* intervalsColSize){
    for(int i=0; i<intervalsSize; i++){
        for(int j=0; j<intervalsSize-i-1; j++){
            if(intervals[j][0] > intervals[j+1][0]){
                swapPointers(&intervals[j], &intervals[j+1]);
            }
        }
    }
}

int** merge(int** intervals, int intervalsSize, int* intervalsColSize, int* returnSize, int** returnColumnSizes) {
    sortMatrix(intervals, intervalsSize, intervalsColSize);

    int start = intervals[0][0];
    int end = intervals[0][1];

    int count=0;
    int **answers = NULL;

    for(int i=1; i<intervalsSize; i++){
        if(end >= intervals[i][0]){
            if(intervals[i][1] < end){
                intervals[i][1] = end;
            }
            end = intervals[i][1];
        }else{
            count++;
            answers = (int **)realloc(answers, sizeof(int*)*count);
            answers[count-1] = (int *)malloc(sizeof(int)*2);
            answers[count-1][0] = start;
            answers[count-1][1] = end;
            start = intervals[i][0];
            end = intervals[i][1];
        }
    }

    count++;
    answers = (int **)realloc(answers, sizeof(int*)*count);
    answers[count-1] = (int *)malloc(sizeof(int)*2);
    answers[count-1][0] = start;
    answers[count-1][1] = end;

    *returnSize = count;
    *returnColumnSizes = (int *)malloc(sizeof(int) * (*returnSize));
    for (int i = 0; i < *returnSize; i++) {
        (*returnColumnSizes)[i] = 2;
    }

    return answers;
}


int main(){
    int rowLength;
    int columnLength = 2;
    
    scanf("%d", &rowLength);
    
    int **matrix = (int **)malloc(sizeof(int *)*rowLength);
    for(int i=0; i<rowLength; i++){
        matrix[i] = (int *)malloc(sizeof(int)*2);
    }

    for(int i=0; i<rowLength; i++){
        for(int j=0; j<2; j++){
            scanf("%d", &matrix[i][j]);
        }
    }
    
    int returnSize = 0;
    int *returnColumnSizes;
    
    int **ansMetrix = merge(matrix, rowLength, &columnLength, &returnSize, &returnColumnSizes);
    
    printf("[");
    for(int i=0; i<returnSize; i++){
        printf("[");
        for(int j=0; j<2; j++){
            printf("%d", ansMetrix[i][j]);
            if(j != 1){
                printf(" ");
            }
        }
        printf("]");
        if(i != returnSize-1){
            printf(",");
        }
    }
    printf("]");
}
