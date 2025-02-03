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

Node* mergeTwoSortedList(Node *head1, Node *head2){
    if(!head1) return head2;
    if(!head2) return head1;

    Node *newHead;
    if(head1->data <= head2->data){
        newHead = head1;
        newHead->next = mergeTwoSortedList(head1->next, head2);
    }else{
        newHead = head2;
        newHead->next = mergeTwoSortedList(head1, head2->next);
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

Node* mergeSort(Node *head){
    if(!head || !head->next) return head;

    Node *midNode = getMidNode(head);
    Node *l1 = head;
    Node *l2 = midNode->next;

    midNode->next = NULL;

    l1 = mergeSort(l1);
    l2 = mergeSort(l2);

    return mergeTwoSortedList(l1, l2);
}

void printList(Node *head){
    Node *current = head;

    while (current != NULL){
        printf("%d -> ", current->data);
        current = current->next;
    }
    
    printf("NULL\n");
}

int main(){
    Node *head = NULL;

    int data;
    while (scanf("%d", &data) == 1){
        insertNode(&head, data);
        if(getchar() == '\n') break;
    }
    printList(head);

    int k;
    scanf("%d", &k);

    head = mergeSort(head);

    Node *current = NULL;
    k -= 1;
    for(current = head; current != NULL && k--; current = current->next);

    printf("%d\n", current->data);
    return 0;
}
