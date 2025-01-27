#include <stdio.h>
#include <stdlib.h>

void merge(int array[], int leftIndex, int middleIndex, int rightIndex) {
    int leftArraySize = middleIndex - leftIndex + 1;
    int rightArraySize = rightIndex - middleIndex;

    int leftSubArray[leftArraySize], rightSubArray[rightArraySize];

    for (int leftCounter = 0; leftCounter < leftArraySize; leftCounter++) {
        leftSubArray[leftCounter] = array[leftIndex + leftCounter];
    }
    for (int rightCounter = 0; rightCounter < rightArraySize; rightCounter++) {
        rightSubArray[rightCounter] = array[middleIndex + 1 + rightCounter];
    }

    int leftPointer = 0, rightPointer = 0, mergePointer = leftIndex;

    while (leftPointer < leftArraySize && rightPointer < rightArraySize) {
        if (leftSubArray[leftPointer] <= rightSubArray[rightPointer]) {
            array[mergePointer++] = leftSubArray[leftPointer++];
        } else {
            array[mergePointer++] = rightSubArray[rightPointer++];
        }
    }

    while (leftPointer < leftArraySize) {
        array[mergePointer++] = leftSubArray[leftPointer++];
    }
    while (rightPointer < rightArraySize) {
        array[mergePointer++] = rightSubArray[rightPointer++];
    }
}

void mergeSort(int array[], int leftIndex, int rightIndex) {
    if (leftIndex < rightIndex) {
        int middleIndex = leftIndex + (rightIndex - leftIndex) / 2;

        mergeSort(array, leftIndex, middleIndex);
        mergeSort(array, middleIndex + 1, rightIndex);

        merge(array, leftIndex, middleIndex, rightIndex);
    }
}

void printArray(int *array, int size) {
    printf("[");
    for (int index = 0; index < size; index++) {
        printf("%d", array[index]);
        if (index != size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

int main() {
    int arraySize;
    printf("Enter the size of the array: ");
    scanf("%d", &arraySize);

    printf("Enter the elements of the array.\n");
    int *inputArray = (int *)malloc(sizeof(int) * arraySize);
    if (inputArray == NULL) {
        printf("Memory allocation failed.\n");
        return 0;
    }

    for (int index = 0; index < arraySize; index++) {
        printf("Enter element at index %d: ", index);
        scanf("%d", &inputArray[index]);
    }

    mergeSort(inputArray, 0, arraySize - 1);

    printf("Sorted Array --> ");
    printArray(inputArray, arraySize);

    free(inputArray);
    return 0;
}
