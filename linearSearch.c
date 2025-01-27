#include <stdio.h>
#include <stdlib.h>

int linearSearch(int array[], int arraySize, int target) {
    for (int index = 0; index < arraySize; index++) {
        if (array[index] == target) {
            return index;
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

    printf("Enter elements in the array:\n");
    for (int i = 0; i < size; i++) {
        printf("Element %d: ", i + 1);
        scanf("%d", &array[i]);
    }

    int target;
    printf("Enter the number to search: ");
    scanf("%d", &target);

    int resultIndex = linearSearch(array, size, target);
    if (resultIndex != -1) {
        printf("Linear Search: Element found at index %d\n", resultIndex);
    } else {
        printf("Linear Search: Element not found\n");
    }

    free(array);
    return 0;
}
