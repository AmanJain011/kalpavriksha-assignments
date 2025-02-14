#include <stdio.h>
#include <stdlib.h>

#define TABLE_SIZE 10
#define MAX_N 100

struct node {
    int key;
    int value;
    struct node* next;
};

struct node* hashTable[TABLE_SIZE] = {NULL};

int hashFunc(int key) {
    return key % TABLE_SIZE;
}

void insert(int key, int value) {
    int index = hashFunc(key);
    struct node* curr = hashTable[index], *prev = NULL;

    while (curr) {
        if (curr->key == key) {
            curr->value = value;
            return;
        }
        prev = curr;
        curr = curr->next;
    }

    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;

    if (!prev) hashTable[index] = newNode;
    else prev->next = newNode;
}

int search(int key) {
    int index = hashFunc(key);
    struct node* curr = hashTable[index];

    while (curr) {
        if (curr->key == key) return curr->value;
        curr = curr->next;
    }
    return -1;
}

void deleteKey(int key) {
    int index = hashFunc(key);
    struct node* curr = hashTable[index], *prev = NULL;

    while (curr) {
        if (curr->key == key) {
            if (!prev) hashTable[index] = curr->next;
            else prev->next = curr->next;
            free(curr);
            return;
        }
        prev = curr;
        curr = curr->next;
    }
}

void clearHashMap() {
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct node* curr = hashTable[i];
        while (curr) {
            struct node* temp = curr;
            curr = curr->next;
            free(temp);
        }
        hashTable[i] = NULL;
    }
}

int main() {
    int arr[MAX_N], n = 0, k;

    while (scanf("%d", &arr[n]) == 1) {
        n++;
        if (getchar() == '\n') break;
    }

    scanf("%d", &k);

    int ans = 0;

    for (int i = 0; i < n; i++) {
        clearHashMap();
        int j = i, distCount = 0;

        while (j < n && distCount <= k) {
            if (search(arr[j]) == -1) {
                insert(arr[j], 1);
                distCount++;
            }
            if (distCount == k) ans++;
            j++;
        }
    }

    printf("%d\n", ans);
    return 0;
}
