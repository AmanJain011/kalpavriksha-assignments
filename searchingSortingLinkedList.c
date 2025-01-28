#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int value;
    struct Node* next;
} Node;

typedef struct LinkedList {
    Node* head;
    Node* tail;
} LinkedList;

Node* split(Node* head);
Node* merge(Node* first, Node* second);
Node* mergeSort(Node* head);
Node* createNode(int value);
void initLinkedList(LinkedList* list);
void insertNode(LinkedList* list, int value);
void printList(LinkedList* list);
double findMedian(Node* head);
void freeList(Node* head);

int main() {
    LinkedList list1, list2, mergedList;
    initLinkedList(&list1);
    initLinkedList(&list2);
    initLinkedList(&mergedList);

    int data;
    char ch;
    printf("Enter list1: ");
    while (scanf("%d", &data) == 1) {
        insertNode(&list1, data);
        scanf("%c", &ch);
        if (ch == '\n') break;
    }

    printf("Enter list2: ");
    while (scanf("%d", &data) == 1) {
        insertNode(&list2, data);
        scanf("%c", &ch);
        if (ch == '\n') break;
    }

    list1.head = mergeSort(list1.head);
    list2.head = mergeSort(list2.head);

    printf("Sorted List 1: ");
    printList(&list1);
    printf("Sorted List 2: ");
    printList(&list2);

    mergedList.head = merge(list1.head, list2.head);

    printf("Merged Sorted List: ");
    printList(&mergedList);

    double median = findMedian(mergedList.head);
    printf("Median: %.1f\n", median);

    freeList(mergedList.head);

    return 0;
}

Node* split(Node* head) {
    Node* fast = head;
    Node* slow = head;

    while (fast != NULL && fast->next != NULL) {
        fast = fast->next->next;
        if (fast != NULL) {
            slow = slow->next;
        }
    }

    Node* temp = slow->next;
    slow->next = NULL;
    return temp;
}

Node* merge(Node* first, Node* second) {
    if (first == NULL) return second;
    if (second == NULL) return first;

    if (first->value < second->value) {
        first->next = merge(first->next, second);
        return first;
    } else {
        second->next = merge(first, second->next);
        return second;
    }
}

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* second = split(head);

    head = mergeSort(head);
    second = mergeSort(second);

    return merge(head, second);
}

Node* createNode(int value) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->value = value;
    newNode->next = NULL;
    return newNode;
}

void initLinkedList(LinkedList* list) {
    list->head = NULL;
    list->tail = NULL;
}

void insertNode(LinkedList* list, int value) {
    Node* newNode = createNode(value);
    if (list->tail == NULL) {
        list->head = newNode;
        list->tail = newNode;
    } else {
        list->tail->next = newNode;
        list->tail = newNode;
    }
}

void printList(LinkedList* list) {
    Node* currentNode = list->head;
    while (currentNode != NULL) {
        printf("%d -> ", currentNode->value);
        currentNode = currentNode->next;
    }
    printf("NULL\n");
}

double findMedian(Node* head) {
    if (head == NULL) {
        return 0;
    }

    Node* slow = head;
    Node* fast = head;

    while (fast != NULL && fast->next != NULL) {
        slow = slow->next;
        fast = fast->next->next;
    }

    if (fast == NULL) {
        Node* prev = head;
        while (prev->next != slow) {
            prev = prev->next;
        }
        return (prev->value + slow->value) / 2.0;
    } else {
        return slow->value;
    }
}

void freeList(Node* head) {
    Node* currentNode = head;
    Node* nextNode;
    while (currentNode != NULL) {
        nextNode = currentNode->next;
        free(currentNode);
        currentNode = nextNode;
    }
}
