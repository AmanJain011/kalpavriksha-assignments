#include <stdio.h>
#include <stdlib.h>

void swapNumbers(int *num1, int *num2) {
    int temp = *num1;
    *num1 = *num2;
    *num2 = temp;
}

int partition(int array[], int start, int end) {
    int pivot = array[end];
    int smallerIndex = start - 1;

    for (int current = start; current < end; current++) {
        if (array[current] < pivot) {
            smallerIndex++;
            swapNumbers(&array[smallerIndex], &array[current]);
        }
    }

    swapNumbers(&array[smallerIndex + 1], &array[end]);
    return smallerIndex + 1;
}

void quickSort(int array[], int start, int end) {
    if (start < end) {
        int pivotIndex = partition(array, start, end);
        quickSort(array, start, pivotIndex - 1);
        quickSort(array, pivotIndex + 1, end);
    }
}

void printArray(int *array, int size) {
    printf("[");
    for (int i = 0; i < size; i++) {
        printf("%d", array[i]);
        if (i != size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
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

    printf("Enter the elements of the array:\n");
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    quickSort(array, 0, size - 1);

    printf("Sorted Array: ");
    printArray(array, size);

    free(array);
    return 0;
}
