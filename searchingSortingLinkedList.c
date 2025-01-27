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

Node* createNode(int value);
void initLinkedList(LinkedList* list);
void insertNode(LinkedList* list, int value);
void printList(LinkedList* list);
Node* mergeSort(Node* head);
Node* merge(Node* left, Node* right);
Node* getMiddle(Node* head);
LinkedList* mergeLists(LinkedList* list1, LinkedList* list2);
double findMedian(Node* head);
void freeList(Node* head);

int main() {
    LinkedList list1, list2;
    initLinkedList(&list1);
    initLinkedList(&list2);

    int data;
    char ch;
    printf("Enter values for list1 (end with newline): ");
    while (scanf("%d", &data) == 1) {
        insertNode(&list1, data);
        scanf("%c", &ch);
        if(ch == '\n') break;
    }

    printf("Enter values for list2 (end with newline): ");
    while (scanf("%d", &data) == 1) {
        insertNode(&list2, data);
        scanf("%c", &ch);
        if(ch == '\n') break;
    }

    printf("List 1: ");
    printList(&list1);
    printf("List 2: ");
    printList(&list2);

    list1.head = mergeSort(list1.head);
    list2.head = mergeSort(list2.head);

    printf("Sorted List 1: ");
    printList(&list1);
    printf("Sorted List 2: ");
    printList(&list2);

    LinkedList* mergedList = mergeLists(&list1, &list2);

    printf("Merged List: ");
    printList(mergedList);

    double median = findMedian(mergedList->head);
    printf("Median: %.1f\n", median);

    freeList(list1.head);
    freeList(list2.head);
    freeList(mergedList->head);
    free(mergedList);

    return 0;
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

Node* mergeSort(Node* head) {
    if (head == NULL || head->next == NULL) {
        return head;
    }

    Node* midNode = getMiddle(head);
    Node* secondHalf = midNode->next;
    midNode->next = NULL;

    Node* left = mergeSort(head);
    Node* right = mergeSort(secondHalf);

    return merge(left, right);
}

Node* merge(Node* left, Node* right) {
    if (left == NULL) return right;
    if (right == NULL) return left;

    if (left->value < right->value) {
        left->next = merge(left->next, right);
        return left;
    } else {
        right->next = merge(left, right->next);
        return right;
    }
}

Node* getMiddle(Node* head) {
    if (head == NULL) return head;

    Node* slowPointer = head;
    Node* fastPointer = head;

    while (fastPointer != NULL && fastPointer->next != NULL) {
        slowPointer = slowPointer->next;
        fastPointer = fastPointer->next->next;
    }

    return slowPointer;
}

LinkedList* mergeLists(LinkedList* list1, LinkedList* list2) {
    LinkedList* mergedList = (LinkedList*)malloc(sizeof(LinkedList));
    initLinkedList(mergedList);

    Node* currentList1 = list1->head;
    Node* currentList2 = list2->head;
    
    while (currentList1 != NULL && currentList2 != NULL) {
        if (currentList1->value < currentList2->value) {
            insertNode(mergedList, currentList1->value);
            currentList1 = currentList1->next;
        } else {
            insertNode(mergedList, currentList2->value);
            currentList2 = currentList2->next;
        }
    }

    while (currentList1 != NULL) {
        insertNode(mergedList, currentList1->value);
        currentList1 = currentList1->next;
    }

    while (currentList2 != NULL) {
        insertNode(mergedList, currentList2->value);
        currentList2 = currentList2->next;
    }

    return mergedList;
}

double findMedian(Node* head) {
    Node* slowPointer = head;
    Node* fastPointer = head;
    int count = 0;

    while (fastPointer != NULL) {
        count++;
        fastPointer = fastPointer->next;
    }

    fastPointer = head;

    if (count % 2 == 0) {
        for (int i = 0; i < count/2 - 1; i++) {
            slowPointer = slowPointer->next;
        }
        return (slowPointer->value + slowPointer->next->value) / 2.0;
    } else {
        for (int i = 0; i < count/2; i++) {
            slowPointer = slowPointer->next;
        }
        return slowPointer->value;
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