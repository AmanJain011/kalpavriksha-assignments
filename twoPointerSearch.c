#include <stdio.h>
#include <stdlib.h>

int twoPointerSearch(int array[], int size, int target) {
    int firstPointer = 0;
    int secondPointer = size-1;
    
    while(firstPointer <= secondPointer){
        if(array[firstPointer] == target){
            return firstPointer;
        }
        if(array[secondPointer] == target){
            return secondPointer;
        }
        firstPointer++;
        secondPointer--;
    }
    return -1;
}

int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *array = (int *)malloc(sizeof(int) * size);
    if (array == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    printf("Enter Sorted elements in the array:\n");
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    int target;
    printf("Enter the number to search: ");
    scanf("%d", &target);

    int resultIndex = twoPointerSearch(array, size, target);
    if (resultIndex != -1) {
        printf("Two Pointer Search: Element found at index %d\n", resultIndex);
    } else {
        printf("Two Pointer Search: Element not found\n");
    }

    free(array);
    return 0;
}
