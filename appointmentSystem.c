#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node{
    int data;
    char *severityLevel;
    struct Node *next;
} Node;

Node* createNode(int data, char *severityLevel){
    Node *node = (Node *)malloc(sizeof(Node));
    node->severityLevel = (char *)malloc(sizeof(char)*10);

    node->data = data;
    node->severityLevel = severityLevel;
    node->next = NULL;
    return node;
}

void insertNode(Node **head, int data, char *severityLevel){
    Node* newNode = createNode(data, severityLevel);

    if(*head == NULL){
        *head = newNode;
        return;
    }

    Node *temp = *head;
    while (temp->next != NULL){
        temp = temp->next;
    }

    temp->next = newNode;
}

void printList(Node *head){
    Node *temp = head;
    while (temp != NULL){
        printf("%d %s\n", temp->data, temp->severityLevel);
        temp = temp->next;
    }
}

int getIndex(Node *temp, char* levels[]){
    for(int i=0; i<3; i++){
        if(!strcmp(temp->severityLevel, levels[i])){
            printf("%d ", i);
            return i;
        }
    }
    return -1;
}

Node *getMid(Node *head){
    if(head == NULL || head->next == NULL) return head;

    Node *slow = head;
    Node *fast = head;

    while (fast->next != NULL){
        slow = slow->next;
        fast = fast->next->next;
    }
    
    return slow;
}

Node* mergeSortedList(Node *l1, Node *l2, char* levels[]){
    if(l1 == NULL) return l2;
    if(l2 == NULL) return l1;

    Node *c1 = l1;
    Node *c2 = l2;
    Node *dummy = createNode(-1, "dummy");
    Node *prev = dummy;

    printf("Running\n");

    while (c1 != NULL && c2 != NULL){
        if(getIndex(c1, levels) < getIndex(c2, levels)){
            prev->next = c1;
            c1 = c1->next;
        }else{
            prev->next = c2;
            c2 = c2->next;
        }

        prev = prev->next;
    }

    prev->next = (c1 != NULL ? c1 : c2);
    return dummy->next;
}

Node* mergeSort(Node *head, char* levels[]){
    if(head == NULL || head->next == NULL) return head;

    Node *midNode = getMid(head);
    Node *newHead = midNode->next;
    midNode->next = NULL;
    Node *temp = head;

    Node* l1 = mergeSort(temp, levels);
    Node* l2 = mergeSort(newHead, levels);

    return mergeSortedList(l1, l2, levels);
}


int main(){
    int k, data;
    scanf("%d", &k);
    
    Node *head = NULL;
    for(int i=0; i<k; i++){
        char* severityLevel = (char *)malloc(sizeof(char)*10);
        scanf("%d %s", &data, severityLevel);
        insertNode(&head, data, severityLevel);
    }

    char* levels[] = {"Critical", "Serious", "Stable"};

    printList(head);

    head = mergeSort(head, levels);
     
    printList(head);
    return 0;
}
