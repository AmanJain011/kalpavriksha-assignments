#include <stdio.h>
#include <stdlib.h>
 
#define TABLE_SIZE 10
 
struct node {
    int key;
    int value;
    struct node* next;
};
 
struct node* hashTable[TABLE_SIZE] = {NULL};
 
void insert(int key, int value) {
    int index = key % TABLE_SIZE;
    struct node* current = hashTable[index];
    struct node* prev = NULL;
 
    while (current != NULL) {
        if (current->key == key) {
            current->value = value;
            return;
        }
        prev = current;
        current = current->next;
    }
 
    struct node* newNode = (struct node*)malloc(sizeof(struct node));
    newNode->key = key;
    newNode->value = value;
    newNode->next = NULL;
 
    if (prev == NULL) {
        hashTable[index] = newNode;
    } else {
        prev->next = newNode;
    }
}
 
int search(int key) {
    int index = key % TABLE_SIZE;
    struct node* current = hashTable[index];
 
    while (current != NULL) {
        if (current->key == key) {
            return current->value;
        }
        current = current->next;
    }
 
    return -1;
}
 
void delete(int key) {
    int index = key % TABLE_SIZE;
    struct node* current = hashTable[index];
    struct node* prev = NULL;
 
    while (current != NULL) {
        if (current->key == key) {
            if (prev == NULL) {
                hashTable[index] = current->next;
            } else {
                prev->next = current->next;
            }
            free(current);
            printf("Key %d deleted.\n", key);
            return;
        }
        prev = current;
        current = current->next;
    }
 
    printf("Key %d not found.\n", key);
}
 
void display() {
    printf("Hash Table:\n");
    for (int i = 0; i < TABLE_SIZE; i++) {
        struct node* current = hashTable[i];
        if (current != NULL) {
            printf("Index %d: ", i);
            while (current != NULL) {
                printf("(%d, %d)", current->key, current->value);
                current = current->next;
                if (current != NULL) {
                    printf(" -> ");
                }
            }
            printf("\n");
        }
    }
}
 
int main() {
    int choice, key, value;
 
    while (1) {
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
 
        switch (choice) {
            case 1:
                printf("Enter key: ");
                scanf("%d", &key);
                printf("Enter value: ");
                scanf("%d", &value);
                insert(key, value);
                break;
            case 2:
                printf("Enter key: ");
                scanf("%d", &key);
                value = search(key);
                if (value != -1) {
                    printf("Value: %d\n", value);
                } else {
                    printf("Key not found.\n");
                }
                break;
            case 3:
                printf("Enter key: ");
                scanf("%d", &key);
                delete(key);
                break;
            case 4:
                display();
                break;
            case 5:
                for (int i = 0; i < TABLE_SIZE; i++) {
                    struct node* current = hashTable[i];
                    while (current != NULL) {
                        struct node* temp = current;
                        current = current->next;
                        free(temp);
                    }
                    hashTable[i] = NULL;
                }
                printf("Exiting program.\n");
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }
 
    return 0;
}
