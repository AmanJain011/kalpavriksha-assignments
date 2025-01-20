#include <stdio.h>
#include <stdlib.h>

typedef struct Node Node;
typedef struct LinkedList LinkedList;

struct Node {
    int data;
    Node *next;
};

struct LinkedList {
    Node *head;
    Node *tail;
    int length;
};

LinkedList *list;

#define MIN_OPERATIONS 1
#define MAX_OPERATIONS 100

void insertAtBeginning(int value);
void insertAtEnd(int value);
void insertAtPosition(int position, int value);
void display();
void updateAtPosition(int position, int newValue);
void deleteAtBeginning();
void deleteAtEnd();
void deleteAtPosition(int position);
void freeList();

int main() {
    list = malloc(sizeof(LinkedList));
    if (!list) {
        printf("Memory allocation failed\n");
        return 1;
    }

    list->head = NULL;
    list->tail = NULL;
    list->length = 0;

    int operationCount;
    scanf("%d", &operationCount);

    if (operationCount < MIN_OPERATIONS || operationCount > MAX_OPERATIONS) {
        printf("Invalid\n");
        free(list);
        return 0;
    }

    while (operationCount--) {
        int choice, value, position;
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                scanf("%d", &value);
                insertAtEnd(value);
                break;

            case 2:
                scanf("%d", &value);
                insertAtBeginning(value);
                break;

            case 3:
                scanf("%d %d", &position, &value);
                insertAtPosition(position, value);
                break;

            case 4:
                display();
                break;

            case 5:
                scanf("%d %d", &position, &value);
                updateAtPosition(position, value);
                break;

            case 6:
                deleteAtBeginning();
                break;

            case 7:
                deleteAtEnd();
                break;

            case 8:
                scanf("%d", &position);
                deleteAtPosition(position);
                break;

            default:
                printf("Invalid\n");
                break;
        }
    }

    freeList();
    free(list);
    return 0;
}

Node *createNode(int data) {
    Node *node = malloc(sizeof(Node));
    if (!node) {
        printf("Memory allocation failed\n");
        return NULL;
    }
    node->data = data;
    node->next = NULL;
    return node;
}

void insertAtBeginning(int value) {
    Node *newNode = createNode(value);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        newNode->next = list->head;
        list->head = newNode;
    }
    list->length++;
}

void insertAtEnd(int value) {
    Node *newNode = createNode(value);
    if (list->head == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
    list->length++;
}

void insertAtPosition(int position, int value) {
    if (position < 1 || position > list->length + 1) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        insertAtBeginning(value);
        return;
    }

    if (position == list->length + 1) {
        insertAtEnd(value);
        return;
    }

    Node *newNode = createNode(value);
    Node *tempNode = list->head;

    for (int i = 1; i < position - 1; i++) {
        tempNode = tempNode->next;
    }

    newNode->next = tempNode->next;
    tempNode->next = newNode;
    list->length++;
}

void display() {
    if (list->head == NULL) {
        printf("List is empty\n");
        return;
    }

    Node *tempNode = list->head;

    while (tempNode != NULL) {
        printf("%d ", tempNode->data);
        tempNode = tempNode->next;
    }

    printf("\n");
}

void updateAtPosition(int position, int newValue) {
    if (position < 1 || position > list->length) {
        printf("Invalid position\n");
        return;
    }

    Node *tempNode = list->head;

    for (int i = 1; i < position; i++) {
        tempNode = tempNode->next;
    }

    tempNode->data = newValue;
}

void deleteAtBeginning() {
    if (list->head == NULL) {
        printf("Invalid position\n");
        return;
    }

    Node *tempNode = list->head;
    list->head = list->head->next;

    if (list->head == NULL) {
        list->tail = NULL;
    }

    free(tempNode);
    list->length--;
}

void deleteAtEnd() {
    if (list->head == NULL) {
        printf("Invalid position\n");
        return;
    }

    if (list->head == list->tail) {
        free(list->head);
        list->head = NULL;
        list->tail = NULL;
    } else {
        Node *tempNode = list->head;

        while (tempNode->next != list->tail) {
            tempNode = tempNode->next;
        }

        free(list->tail);
        list->tail = tempNode;
        tempNode->next = NULL;
    }

    list->length--;
}

void deleteAtPosition(int position) {
    if (position < 1 || position > list->length) {
        printf("Invalid position\n");
        return;
    }

    if (position == 1) {
        deleteAtBeginning();
        return;
    }

    if (position == list->length) {
        deleteAtEnd();
        return;
    }

    Node *tempNode = list->head;

    for (int i = 1; i < position - 1; i++) {
        tempNode = tempNode->next;
    }

    Node *nodeToDelete = tempNode->next;
    tempNode->next = nodeToDelete->next;
    free(nodeToDelete);

    list->length--;
}

void freeList() {
    Node *current = list->head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
    list->head = NULL;
    list->tail = NULL;
    list->length = 0;
}
