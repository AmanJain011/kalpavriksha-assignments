#include <stdio.h>
#include <stdlib.h>

void targetSubsetSum(int *array, int length, int target, int *subSet, int subSetLength, int subSetSum, int idx){
    if(subSetSum == target){
        printf("[");
        for(int i=0; i<subSetLength; i++){
            printf("%d", subSet[i]);
            if(i != subSetLength-1){
                printf(" ");
            }
        }
        printf("]\n");
    }
    
    for(int i=idx; i<length; i++){
        if(i-1 >= idx && array[i] == array[i-1]) continue;
        subSet[subSetLength] = array[i];
        targetSubsetSum(array, length, target, subSet, subSetLength+1, subSetSum+array[i], i+1);
    }
}

void swap(int *value1, int *value2){
    int temp = *value1;
    *value1 = *value2;
    *value2 = temp;
}

void sortArray(int *array, int length){
    for(int i=0; i<length; i++){
        for(int j=0; j<length-i-1; j++){
            if(array[j] > array[j+1]){
                swap(&array[j], &array[j+1]);
            }
        }
    }
}

int main()
{
    int length, target;
    
    printf("Enter length of the array: ");
    scanf("%d", &length);
    
    printf("Enter target: ");
    scanf("%d", &target);
    
    int *numberArray = (int *)malloc(sizeof(int)*length);
    for(int i=0; i<length; i++){
        printf("Enter value at index %d: ", i);
        scanf("%d", &numberArray[i]);
    }
    
    sortArray(numberArray, length);
    
    int *subSet = (int *)malloc(sizeof(int)*length);
    
    targetSubsetSum(numberArray, length, target, subSet, 0, 0, 0);

    return 0;
}
