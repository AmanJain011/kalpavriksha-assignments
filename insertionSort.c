#include <stdio.h>
#include <stdlib.h>

void insertionSort(int *array, int length){
    for(int pass = 0; pass < length; pass++){
        int currenValue = array[pass];
        int previousIndex = pass - 1;

        while (previousIndex >= 0 && array[previousIndex] > currenValue){
            array[previousIndex + 1] = array[previousIndex];
            previousIndex--;
        }

        array[previousIndex + 1] = currenValue;
    }
}

void printArray(int *array, int length){
    printf("[");
    for(int idx = 0; idx < length; idx++){
        printf("%d", array[idx]);
        if(idx != length-1){
            printf(", ");
        }
    }
    printf("]\n");
}

int main(){
    int length; 
    printf("Enter length of the Array: ");
    scanf("%d", &length);

    printf("Enter array elements.\n");
    int *numberArray = (int *)malloc(sizeof(int)*length);
    if(numberArray == NULL){
        printf("Memory doesn't assigne to the Array.\n");
        return 0;
    }

    for(int idx = 0; idx < length; idx++){
        printf("Enter at index (%d): ", idx);
        scanf("%d", &numberArray[idx]);
    }

    insertionSort(numberArray, length);

    printf("Sorted Array --> ");
    printArray(numberArray, length);

    free(numberArray);
    return 0;
}