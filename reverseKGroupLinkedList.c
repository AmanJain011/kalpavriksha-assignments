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

Node* reverseList(Node *node, int k) {
    Node *current = node;
    Node *next = NULL;
    Node *previous = NULL;
    int count = 0;

    while (current != NULL && count < k) {
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
        count++;
    }

    if (node != NULL) {
        node->next = current;
    }

    return previous;
}


void reverseKGroupLinkedList(LinkedList *list, int k) {
    if (k <= 1 || list->length < k) return;

    Node *current = list->head;
    Node *newHead = NULL;
    Node *previousTail = NULL;

    while (current != NULL) {
        Node *segmentHead = current;
        Node *segmentTail = current;

        int count = 0;
        while (current != NULL && count < k) {
            current = current->next;
            count++;
        }

        if (count < k) {
            if (previousTail != NULL) {
                previousTail->next = segmentHead;
            }
            break;
        }

        Node *reversedHead = reverseList(segmentHead, k);

        if (newHead == NULL) {
            newHead = reversedHead;
        }
        if (previousTail != NULL) {
            previousTail->next = reversedHead;
        }

        previousTail = segmentTail;

        count = 0;
        while (current != NULL && count < k) {
            previousTail = current;
            current = current->next;
            count++;
        }
    }

    list->head = newHead;
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
