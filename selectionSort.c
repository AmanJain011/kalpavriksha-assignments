#include <stdio.h>
#include <stdlib.h>

void swapNumber(int *value1, int *value2){
    int tempValue = *value1;
    *value1 = *value2;
    *value2 = tempValue;
}

void selectionSort(int *array, int length){
    for(int i = 0; i < length-1; i++){
        int minimumIndex = i;
        for(int j = i+1; j < length; j++){
            if(array[j] < array[minimumIndex]){
                minimumIndex = j;
            }
        }

        swapNumber(&array[i], &array[minimumIndex]);
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

    selectionSort(numberArray, length);

    printf("Sorted Array --> ");
    printArray(numberArray, length);

    free(numberArray);
    return 0;
}