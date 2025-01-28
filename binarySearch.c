#include <stdio.h>
#include <stdlib.h>

int binarySearch(int arr[], int size, int target) {
    int left = 0, right = size - 1;
    while (left <= right) {
        int middle = left + (right - left) / 2;

        if (arr[middle] == target) {
            return middle;
        } else if (arr[middle] < target) {
            left = middle + 1;
        } else {
            right = middle - 1;
        }
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

    int resultIndex = binarySearch(array, size, target);
    if (resultIndex != -1) {
        printf("Binary Search: Element found at index %d\n", resultIndex);
    } else {
        printf("Binary Search: Element not found\n");
    }

    free(array);
    return 0;
}
