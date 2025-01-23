#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

typedef struct LinkedList {
    Node *head;
    Node *tail;
    int length;
} LinkedList;

Node* createNode(int data) {
    Node *node = malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    return node;
}

void insertNode(LinkedList *list, int data) {
    Node *newNode = createNode(data);
    if (list->head == NULL) {
        list->head = newNode;
    } else {
        list->tail->next = newNode;
    }
    list->tail = newNode;
    list->length++;
}

void addFirstNode(Node **tempHead, Node **tempTail, Node *node) {
    if (*tempHead == NULL) {
        *tempHead = node;
        *tempTail = node;
    } else {
        node->next = *tempHead;
        *tempHead = node;
    }
}

void reverseKGroupLinkedList(LinkedList *list, int k) {
    if (k <= 1 || list->length < k) return;

    Node *current = list->head;
    Node *forward = NULL;
    Node *orignalHead = NULL;
    Node *orignalTail = NULL;

    while (current != NULL) {
        Node *tempHead = NULL;
        Node *tempTail = NULL;
        int count = 0;

        while (current != NULL && count < k) {
            forward = current->next;
            current->next = NULL;
            addFirstNode(&tempHead, &tempTail, current);
            current = forward;
            count++;
        }

        if (orignalHead == NULL) {
            orignalHead = tempHead;
            orignalTail = tempTail;
        } else {
            orignalTail->next = tempHead;
            orignalTail = tempTail;
        }
    }

    list->head = orignalHead;
    list->tail = orignalTail;
}

void printLinkedList(LinkedList *list) {
    Node *current = list->head;
    while (current != NULL) {
        printf("%d ", current->data);
        current = current->next;
    }
    printf("\n");
}

int main() {
    LinkedList list = {NULL, NULL, 0};

    int data;
    char character;
    while (scanf("%d", &data) == 1) {
        insertNode(&list, data);
        scanf("%c", &character);
        if (character == '\n') break;
    }

    int k;
    scanf("%d", &k);

    reverseKGroupLinkedList(&list, k);
    printLinkedList(&list);

    return 0;
}
