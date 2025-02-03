#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct Node{
    int data;
    struct Node *next;
} Node;

Node *createNode(int data){
    Node *node = (Node *)malloc(sizeof(Node));
    if(!node) return NULL;

    node->data = data;
    node->next = NULL;

    return node;
}

void insertNode(Node **head, int data){
    Node *newNode = createNode(data);

    if(!(*head)){
        *head = newNode;
        return;
    }

    Node *current = *head;
    while (current->next != NULL){
        current = current->next;
    }
    
    current->next = newNode;
}

Node* mergeTwoSortedList(Node *head1, Node *head2, bool isDescending){
    if(!head1) return head2;
    if(!head2) return head1;

    Node *newHead;
    if(isDescending ? head1->data >= head2->data : head1->data <= head2->data){
        newHead = head1;
        newHead->next = mergeTwoSortedList(head1->next, head2, isDescending);
    }else{
        newHead = head2;
        newHead->next = mergeTwoSortedList(head1, head2->next, isDescending);
    }

    return newHead;
}

Node *getMidNode(Node *head){
    if(!head || !head->next) return head;

    Node *slow = head;
    Node *fast = head;

    while (fast->next != NULL && fast->next->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

Node* evenOddSortedListmergeSort(Node *head, bool isDescending){
    if(!head || !head->next) return head;

    Node *midNode = getMidNode(head);
    Node *l1 = head;
    Node *l2 = midNode->next;

    midNode->next = NULL;

    l1 = mergeSort(l1, isDescending);
    l2 = mergeSort(l2, isDescending);

    return mergeTwoSortedList(l1, l2, isDescending);
}

void printList(Node *head){
    Node *current = head;

    while (current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }

    printf("NULL\n");
}

void oddEvenList(Node *head, Node **oddList, Node **evenList){
    if(!head) return;

    Node *current = head;
    Node *tempNode = NULL;

    Node *oddTail = NULL;
    Node *evenTail = NULL;

    while (current != NULL){
        tempNode = current;
        current = current->next;
        tempNode->next = NULL;

        if(tempNode->data & 1){
            if(!*oddList){
                *oddList = oddTail = tempNode;
            }else{
                oddTail->next = tempNode;
                oddTail = tempNode;
            }
        }else{
            if(!*evenList){
                *evenList = evenTail = tempNode;
            }else{
                evenTail->next = tempNode;
                evenTail = tempNode;
            }
        }
    }
}

int main(){
    Node *head = NULL;

    int data;
    while (scanf("%d", &data) == 1){
        insertNode(&head, data);
        if(getchar() == '\n') break;
    }
    
    Node *oddList = NULL;
    Node *evenList = NULL;

    oddEvenList(head, &oddList, &evenList);
    evenList = mergeSort(evenList, false);
    oddList = mergeSort(oddList, true);

    if (!evenList){
        printList(oddList);
        return 0;
    }

    if (!oddList){
        printList(evenList);
        return 0;
    }
    
    Node *current = evenList;
    while (current->next != NULL){
        current = current->next;
    }

    current->next = oddList;

    printList(evenList);
    
    return 0;
}
