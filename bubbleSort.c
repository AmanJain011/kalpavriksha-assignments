#include <stdio.h>
#include <stdlib.h>

void swapNumber(int *value1, int *value2){
    int tempValue = *value1;
    *value1 = *value2;
    *value2 = tempValue;
}

void bubbleSort(int *array, int length){
    for(int i = 0; i < length-1; i++){
        int swapped = 0;
        for(int j = 0; j < length-i- 1; j++){
            if(array[j] > array[j+1]){
                swapNumber(&array[j], &array[j+1]);
                swapped = 1;
            }
        }

        if (swapped == 0) break;
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

    bubbleSort(numberArray, length);

    printf("Sorted Array --> ");
    printArray(numberArray, length);

    free(numberArray);
    return 0;
}